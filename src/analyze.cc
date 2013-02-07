#include "analyze.h"

namespace beelzebub{
	Analyzer::Analyzer(){

	}


	Analyzer::~Analyzer(){

	}

	// codeという名前が適切か、逆アセンブル作成時に検討
	unsigned char *Analyzer::get_code(){
		return this->code_;
	}

	
	void Analyzer::set_pe_signature_address(unsigned char *signature_address){
		this->pe_signature_address_ = signature_address;

		return;
	}


	// ファイルサイズを取得するように作り替え
	void Analyzer::Read(char *filename, int size){
		FILE *fp;

		this->code_ = new unsigned char[size];
		this->code_size_ = size;

		fp = fopen(filename, "rb");
		if(fp == NULL){
			std::cerr << "Error: could not open \"" << filename << "\"" << std::endl;
			exit(EXIT_FAILURE);
		}

		fread(this->code_, sizeof(unsigned char), size, fp);

		return;
	}


	void Analyzer::Read(char *filename){
		int size = 40960;

		this->Read(filename, size);

		return;
	}


	void Analyzer::Run(){
		this->SearchPeSignature();
		this->GetPeHeader();
		this->ShowPeHeader();
		this->SearchImportTable();
		this->ExtractImageImportDescriptor();
		this->ExtractDLL();
		this->ExtractAPI();
		this->ShowDLL();
		this->ShowAPI();

		return;
	}


	unsigned char *Analyzer::SearchSignature(unsigned char *signature){
		unsigned char *signature_address;

		signature_address = std::search(this->code_, this->code_ + this->code_size_, signature, signature + strlen((const char *)signature));
		if(signature_address == NULL){
			std::cerr << "Error: could not find \"" << signature << "\" signature" << std::endl;
			exit(EXIT_FAILURE);
		}

		return signature_address;
	}


	void Analyzer::SearchPeSignature(){
		unsigned char pe_signature[] = "PE";

		this->pe_signature_address_ = this->SearchSignature(pe_signature);

		return;
	}


	void Analyzer::GetPeHeader(){
		this->pe_header_ = (IMAGE_NT_HEADER32 *)this->pe_signature_address_;

		return;
	}


	void Analyzer::ShowPeHeader(){
		std::cout.setf(std::ios::hex, std::ios::basefield);
		std::cout.setf(std::ios::showbase);
		std::cout << "SizeOfCode: " << this->pe_header_->OptionalHeader.SizeOfCode << std::endl;
		std::cout << "AddressOfEntryPoint: " << this->pe_header_->OptionalHeader.AddressOfEntryPoint << std::endl;
		std::cout << "BaseOfCode: " << this->pe_header_->OptionalHeader.BaseOfCode << std::endl;
		std::cout << "BaseOfData: " << this->pe_header_->OptionalHeader.BaseOfData << std::endl;
		std::cout << "ImportTableAddress: " << this->pe_header_->OptionalHeader.DataDirectory[1].RVA << std::endl;
		std::cout << "ImportAddressTableAddress: " << this->pe_header_->OptionalHeader.DataDirectory[12].RVA << std::endl;

		return;
	}


	void Analyzer::SearchImportTable(){
		unsigned int import_table_address_rva;

		import_table_address_rva = this->pe_header_->OptionalHeader.DataDirectory[1].RVA;
		this->import_table_address_ = this->code_ + import_table_address_rva;

		return;
	}


	void Analyzer::ExtractImageImportDescriptor(){
		IMAGE_IMPORT_DESCRIPTOR *pointer;

		pointer = (IMAGE_IMPORT_DESCRIPTOR *)this->import_table_address_;

		this->dll_num_ = 0;
		
		while(true){
			if(this->IsEndOfImageImportDescriptorTable((unsigned char *)pointer) == true) break;
			this->image_import_descriptor_.push_back(pointer);
			pointer += 1;
			this->dll_num_++;
		}

		return;
	}


	bool Analyzer::IsEndOfImageImportDescriptorTable(unsigned char *pointer){
		for(int i=0;i<20;i++){
			if(*pointer != 0x00) return false;
			pointer++;
		}

		return true;
	}


	void Analyzer::ExtractDLL(){
		for(int i=0;i<this->dll_num_;i++){
			this->DLL.push_back((char *)(this->code_ + this->image_import_descriptor_[i]->Name));
			/*
			#ifdef DEBUG
				std::cout << this->image_import_descriptor_[i]->Name << std::endl;
			#endif
			*/
		}

		return;
	}


	void Analyzer::ShowDLL(){
		for(int i=0;i<this->DLL.size();i++){
			std::cout << this->DLL[i] << std::endl;
		}

		return;
	}


	// DLLとAPIの対応付けを明示できるようにする．
	void Analyzer::ExtractAPI(){
		unsigned int *pointer;

		for(int i=0;i<this->dll_num_;i++){
			pointer = (unsigned int *)(this->code_ + this->image_import_descriptor_[i]->OriginalFirstThunk);
			while(*pointer != 0){
				this->API.push_back((IMAGE_IMPORT_BY_NAME *)(this->code_ + *pointer));
				#ifdef DEBUG
					// std::cout << this->API.Name << std::endl;
				#endif
				pointer += 1;
			}
		}

		return;
	}


	void Analyzer::ShowAPI(){
		for(int i=0;i<this->API.size();i++){
			std::cout << this->API[i]->Name << std::endl;
		}

		return;
	}
}
