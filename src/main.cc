#include "main.h"

using namespace beelzebub;

// namespace beelzebub {

int main(int argc, char **argv){
  char *malware_name;
  int file_size;
  beelzebub::Analyzer *analyzer;
  beelzebub::Disassembler *disasm;

  malware_name = argv[1];

  if(argc != 2){
    std::cerr << "Usage: beelzebub (malware file name)" << std::endl;
    exit(EXIT_FAILURE);
  }

  analyzer = new beelzebub::Analyzer;
  disasm = new beelzebub::Disassembler;
  analyzer->Read(malware_name);
  analyzer->Run();
  disasm->set_size_of_code(analyzer->get_size_of_code());
  disasm->set_base_of_code(analyzer->get_base_of_mapped_code());
  // disasm->DisassembleCode();
  disasm->ConstructRestrictedInstruction();
  delete analyzer;
  delete disasm;

  return 0;
}

//}  // namespace beelzebub
