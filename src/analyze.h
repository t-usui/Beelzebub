#ifndef BEELZEBUB_ANALYZE_H_
#define BEELZEBUB_ANALYZE_H_
#define DEBUG

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "winnt.h"

namespace beelzebub{

class Analyzer{
 public:
  // Constructor, Destructor
  Analyzer();
  ~Analyzer();

  // Accessor, Mutator
  unsigned char *get_base_of_code();
  unsigned char *get_base_of_mapped_code();
  int get_size_of_code();
  // Member method
  void Read(char *filename);
  void Run();
  unsigned char *SearchSignature(unsigned char *signature);
  void SearchPeSignature();
  void GetPeHeader();
  void ShowPeHeader();
  void MapImageOnMemory();
  void SearchImportTable();
  void ExtractImageImportDescriptor();
  bool IsEndOfImageImportDescriptorTable(unsigned char *pointer);
  void ExtractDLL();
  void ShowDLL();
  void ExtractAPI();
  void ShowAPI();

 private:
  int GetFileSize(FILE *fp);

  // Code
  unsigned char *code_;
  int code_size_;
  // Image
  unsigned char *mapped_image_;
  unsigned char *base_of_code_;
  int size_of_code_;
  // PE header
  unsigned char *pe_signature_address_;
  IMAGE_NT_HEADER32 *pe_header_;
  // Section
  IMAGE_SECTION_HEADER *image_section_header_;
  // Import Section
  unsigned char *import_table_address_;
  std::vector<IMAGE_IMPORT_DESCRIPTOR *> image_import_descriptor_;
  int dll_num_;
  std::vector<std::string> DLL;
  std::vector<IMAGE_IMPORT_BY_NAME *> API;
};

}  // namespace beelzebub

#endif  // BEELZEBUB_ANALYZE_H_
