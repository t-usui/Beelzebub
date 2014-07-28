#ifndef BEELZEBUB_DISASM_H_
#define BEELZEBUB_DISASM_H_

#include <udis86.h>
#include <iostream>
#include <string.h>

union _restricted_instruction {
  char byte[4];
  uint32_t dword;
};

namespace beelzebub{

class Disassembler{
 public:
  Disassembler();
  ~Disassembler();

  // Mutator
  void set_base_of_code(unsigned char *base_of_code);
  void set_size_of_code(int size_of_code);
  // Member method
  void DisassembleCode();
  void ConstructRestrictedInstruction();

 private:
  ud_t ud_obj_;
  unsigned char *base_of_code_;
  int size_of_code_;
  int ProcessPrefix(ud_t ud_obj,
                    union _restricted_instruction *restricted_instruction);
  unsigned char DistinguishSegment(ud_t ud_obj, int prefix_length);
  int ProcessOpcode(ud_t ud_obj, int prefix_length,
                    union _restricted_instruction *restricted_instruction);
  void ProcessModRMAndSIB(ud_t ud_obj, int prefix_length, int opcode_length,
                          union _restricted_instruction *restricted_instruction);
//  void ProcessSIB(ud_t ud_obj, int prefix_length, int opcode_length);
};

}  // namespace beelzebub

#endif  // BEELZEBUB_DISASM_H_
