#include "analyze.h"

namespace beelzebub {

Analyzer::Analyzer(){

}

Analyzer::~Analyzer(){

}

unsigned char *Analyzer::get_base_of_code(){
  return this->base_of_code_;
}

unsigned char *Analyzer::get_base_of_mapped_code() {
  return reinterpret_cast<unsigned char *>(this->mapped_image_ + this->pe_header_->OptionalHeader.BaseOfCode);
}

int Analyzer::get_size_of_code(){
  return this->size_of_code_;
}

void Analyzer::Read(char *filename){
  FILE *fp;

  fp = fopen(filename, "rb");

  if (fp == NULL) {
    std::cerr << "Error: could not open \"" << filename << "\"" << std::endl;
    exit(EXIT_FAILURE);
  }

  this->code_size_ = this->GetFileSize(fp);
  this->code_ = new unsigned char[this->code_size_];
  std::cout << "FileSize:" << this->code_size_ << std::endl;
  fread(this->code_, sizeof(this->code_[0]), this->code_size_, fp);
}

int Analyzer::GetFileSize(FILE *fp){
  int file_size;

  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  return file_size;
}

void Analyzer::Run(){
  this->SearchPeSignature();
  this->GetPeHeader();
  this->ShowPeHeader();
  this->MapImageOnMemory();
//  this->SearchImportTable();
//  this->ExtractImageImportDescriptor();
//  this->ExtractDLL();
//  this->ShowDLL();
//  this->ExtractAPI();
//  this->ShowAPI();
}

unsigned char *Analyzer::SearchSignature(unsigned char *signature){
  unsigned char *signature_address;

  signature_address = std::search(this->code_,
                                  this->code_ + this->code_size_,
                                  signature,
                                  signature + strlen(reinterpret_cast<const char *>(signature)));

  if (signature_address == NULL) {
    std::cerr << "Error: could not find \"" << signature << "\" signature" << std::endl;
    exit(EXIT_FAILURE);
  }

  return signature_address;
}

void Analyzer::SearchPeSignature(){
  unsigned char pe_signature[] = "PE\0\0";

  this->pe_signature_address_ = this->SearchSignature(pe_signature);
}

void Analyzer::GetPeHeader(){
  this->pe_header_ = reinterpret_cast<IMAGE_NT_HEADER32 *>(this->pe_signature_address_);

  // SizeOfCode, BaseOfCode
  this->size_of_code_ = this->pe_header_->OptionalHeader.SizeOfCode;
  this->base_of_code_ = reinterpret_cast<unsigned char *>(this->code_ + this->pe_header_->OptionalHeader.BaseOfCode);
}

void Analyzer::ShowPeHeader(){
  printf("MajorLinkerVersion: %x\n", this->pe_header_->OptionalHeader.MajorLinkerVersion);
  printf("MinorLinkerVersion: %x\n", this->pe_header_->OptionalHeader.MinorLinkerVersion);
  // Somehow commented-out codes below does not work well (space is returned)
  // std::cout << "MajorLinkerVersion: " << this->pe_header_->OptionalHeader.MajorLinkerVersion << std::endl;
  // std::cout << "MinorLinkerVersion: " << this->pe_header_->OptionalHeader.MinorLinkerVersion << std::endl;
  std::cout.setf(std::ios::hex, std::ios::basefield);
  std::cout.setf(std::ios::showbase);
  std::cout << "SectionAlignment: " << this->pe_header_->OptionalHeader.SectionAlignment << std::endl;
  std::cout << "FileAlignment: " << this->pe_header_->OptionalHeader.FileAlignment << std::endl;
  std::cout << "SizeOfCode: " << this->pe_header_->OptionalHeader.SizeOfCode << std::endl;
  std::cout << "AddressOfEntryPoint: " << this->pe_header_->OptionalHeader.AddressOfEntryPoint << std::endl;
  std::cout << "BaseOfCode: " << this->pe_header_->OptionalHeader.BaseOfCode << std::endl;
  std::cout << "BaseOfData: " << this->pe_header_->OptionalHeader.BaseOfData << std::endl;
  std::cout << "ImportTableAddress: " << this->pe_header_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].RVA << std::endl;
  std::cout << "ImportAddressTableAddress: " << this->pe_header_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].RVA << std::endl;
}

void Analyzer::MapImageOnMemory(){
  this->mapped_image_ = new unsigned char[this->pe_header_->OptionalHeader.SizeOfImage];

  if (this->mapped_image_ == NULL) {
    std::cerr << "Error: mapping image" << std::endl;
    exit(EXIT_FAILURE);
  }

  this->image_section_header_ = reinterpret_cast<IMAGE_SECTION_HEADER *>(this->pe_header_ + 1);
  // map header
  memcpy(this->mapped_image_, this->code_, this->pe_header_->OptionalHeader.SizeOfHeaders);
  // map section data
  std::cout << "Number of sections: " << this->pe_header_->FileHeader.NumberOfSections << std::endl;
  for (int i=0; i<this->pe_header_->FileHeader.NumberOfSections; i++) {
    if (this->image_section_header_[i].PointerToRawData) {
      memcpy(&this->mapped_image_[image_section_header_[i].VirtualAddress],
             &this->code_[image_section_header_[i].PointerToRawData],
             image_section_header_[i].SizeOfRawData);
      std::cout << i << std::endl;
      std::cout << image_section_header_[i].PointerToRawData << std::endl;
    }
  }
  FILE *fp;
  fp = fopen("./temp", "w");
  fwrite(this->mapped_image_, 1, this->pe_header_->OptionalHeader.SizeOfImage, fp);
  fclose(fp);
}

void Analyzer::SearchImportTable(){
  unsigned int import_table_address_rva;

  import_table_address_rva = this->pe_header_->OptionalHeader.DataDirectory[1].RVA;
  this->import_table_address_ = this->mapped_image_ + import_table_address_rva;
}

void Analyzer::ExtractImageImportDescriptor(){
  IMAGE_IMPORT_DESCRIPTOR *pointer;

  pointer = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR *>(this->import_table_address_);
  this->dll_num_ = 0;
  while (true) {
    if (this->IsEndOfImageImportDescriptorTable(reinterpret_cast<unsigned char *>(pointer)) == true) break;
    this->image_import_descriptor_.push_back(pointer);
    pointer += 1;
    this->dll_num_++;
  }
}

bool Analyzer::IsEndOfImageImportDescriptorTable(unsigned char *pointer){
  for (int i=0; i<20; i++) {
    if (*pointer != 0x00) return false;
      pointer++;
    }
  return true;
}

void Analyzer::ExtractDLL(){
  for (int i=0; i<this->dll_num_; i++) {
    this->DLL.push_back(reinterpret_cast<char *>(this->mapped_image_ + this->image_import_descriptor_[i]->Name));
    #ifdef DEBUG
      std::cout << this->image_import_descriptor_[i]->Name << std::endl;
    #endif
  }
}

void Analyzer::ShowDLL(){
  for (int i=0; i<this->DLL.size(); i++) {
    std::cout << this->DLL[i] << std::endl;
  }
}

// TODO: Demonstrate the correspondence between DLL and API.
void Analyzer::ExtractAPI(){
  unsigned int *pointer;
  IMAGE_IMPORT_DESCRIPTOR *p;

  for (int i=0; i<this->dll_num_; i++) {
    pointer = reinterpret_cast<unsigned int *>(this->mapped_image_ + this->image_import_descriptor_[i]->OriginalFirstThunk);
    while (*pointer != 0) {
      printf("%p\n", this->mapped_image_ + *pointer);
      this->API.push_back(reinterpret_cast<IMAGE_IMPORT_BY_NAME *>(this->mapped_image_ + *pointer));
      pointer += 1;
    }
  }
}

void Analyzer::ShowAPI(){
  for (int i=0; i<this->API.size(); i++) {
    std::cout << this->API[i]->Name << std::endl;
  }
}

}  // namespace
