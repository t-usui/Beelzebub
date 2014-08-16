#include "disasm.h"

namespace beelzebub {

Disassembler::Disassembler(){
  ud_init(&(this->ud_obj_));
}

Disassembler::~Disassembler(){

}

void Disassembler::set_base_of_code(unsigned char *base_of_code){
  this->base_of_code_ = base_of_code;
}

void Disassembler::set_size_of_code(int size_of_code){
  this->size_of_code_ = size_of_code;
}

// for general disassemble
void Disassembler::DisassembleCode(){
  // std::cout << "Start disassembling..." << std::endl;
  // std::cout << this->base_of_code_ << std::endl;
  // std::cout << this->size_of_code_ << std::endl;
  ud_set_input_buffer(&(this->ud_obj_), this->base_of_code_, this->size_of_code_);
  ud_set_mode(&(this->ud_obj_), 32);
  ud_set_syntax(&(this->ud_obj_), UD_SYN_INTEL);
  while(ud_disassemble(&(this->ud_obj_))){
    std::cout << "\t" << ud_insn_asm(&(this->ud_obj_)) << std::endl;
  }
}

// for Iwamura System
void Disassembler::ConstructRestrictedInstruction() {
  int instruction_length;
  int prefix_length;
  int opcode_length;
  union _restricted_instruction restricted_instruction;

  std::cout << "Start constructing..." << std::endl;
  // std::cout << this->base_of_code_ << std::endl;
  // std::cout << this->size_of_code_ << std::endl;
  ud_set_input_buffer(&(this->ud_obj_), this->base_of_code_,
                      this->size_of_code_);
  ud_set_mode(&(this->ud_obj_), 32);
  ud_set_syntax(&(this->ud_obj_), UD_SYN_INTEL);

  while(ud_disassemble(&(this->ud_obj_)) != 0){
    restricted_instruction.dword = 0x00000000;
    instruction_length = ud_insn_len(&(this->ud_obj_));
    std::cout << "Instruction length: " << instruction_length << std::endl;

    prefix_length = 0;
    opcode_length = 0;
    prefix_length = this->ProcessPrefix(this->ud_obj_, &restricted_instruction);
    opcode_length = this->ProcessOpcode(this->ud_obj_, prefix_length,
                                        &restricted_instruction);
    this->ProcessModRMAndSIB(this->ud_obj_, prefix_length, opcode_length,
                             &restricted_instruction);

    std::cout << "Restricted instruction: "
              << restricted_instruction.dword << std::endl;

    std::cout << ud_insn_hex(&(this->ud_obj_)) << std::endl;
    std::cout << ud_insn_asm(&(this->ud_obj_)) << std::endl;
    std::cout << std::endl;
  }
}

int Disassembler::ProcessPrefix(ud_t ud_obj,
                    union _restricted_instruction *restricted_instruction) {
  int prefix_length = 0;
  unsigned char segment_prefix;
  
  // For Group 1 prefix
  if (ud_obj.pfx_rep != UD_NONE) { // REP: assign 01
    (*restricted_instruction).byte[0] |= 0x40;
    prefix_length++;
  } else if (ud_obj.pfx_repne != UD_NONE) { // REPNE: assign 10
    (*restricted_instruction).byte[0] |= 0x80;
    prefix_length++;
  } else if (ud_obj.pfx_lock != UD_NONE) { // LOCK: assign 11
    (*restricted_instruction).byte[0] |= 0xc0;
    prefix_length++;
  } else { // None
    // std::cout << "\t" << "None (Group 1)" << std::endl;
  }

  // For Group 3 prefix
  if (ud_obj.pfx_opr != UD_NONE) { // OPR
    (*restricted_instruction).byte[0] |= 0x04;
    prefix_length++;
  } else {
    // std::cout << "\t" << "None (Group 3)" << std::endl;
  }

  // For Group 4 prefix
  if (ud_obj.pfx_adr != UD_NONE) { // ADR
    (*restricted_instruction).byte[0] |= 0x02;
    prefix_length++;
  } else {
    // std::cout << "\t" << "None (Group 4)" << std::endl;
  }

  // For Group 2 prefix
  if (ud_obj.pfx_seg != UD_NONE) { // SEG
    prefix_length++;
    segment_prefix = DistinguishSegment(ud_obj, prefix_length);
    switch (segment_prefix) {
      case 0x2e: // assign 001
        (*restricted_instruction).byte[0] |= 0x08;
        break;
      case 0x36: // assign 010
        (*restricted_instruction).byte[0] |= 0x10;
        break;
      case 0x3e: // assign 011
        (*restricted_instruction).byte[0] |= 0x18;
        break;
      case 0x26: // assign 100
        (*restricted_instruction).byte[0] |= 0x20;
        break;
      case 0x64: // assign 101
        (*restricted_instruction).byte[0] |= 0x28;
        break;
      case 0x65: // assign 110
        (*restricted_instruction).byte[0] |= 0x30;
        break;
      default:
        std::cerr << "Error: undefined segment prefix" << std::endl;
        exit(EXIT_FAILURE);
    }
  } else { // None
    // std::cout << "\t" << "None (Group 2)" << std::endl;
  }
  std::cout << "Prefix length: " << prefix_length << std::endl;

  return prefix_length;
}

unsigned char Disassembler::DistinguishSegment(ud_t ud_obj, int prefix_length) {
  unsigned char *instruction_ptr;
  unsigned char prefix[prefix_length + 1];
  unsigned char *prefix_ptr;
  unsigned char segment_prefix[] = { 0x2e, 0x36, 0x3e, 0x26, 0x64, 0x65 };

  instruction_ptr = (unsigned char *)ud_insn_ptr(&ud_obj);
  prefix_ptr = instruction_ptr;

  memcpy(prefix, instruction_ptr, prefix_length);

  while (*prefix_ptr != '\0') {
    for (int i = 0; i < sizeof(segment_prefix); i++) {
      if (*prefix_ptr == segment_prefix[i]) return segment_prefix[i];
    }
    prefix_ptr++;
  }

  std::cerr << "Error: cannot distinguish segment prefix" << std::endl;
  exit(EXIT_FAILURE);
}

int Disassembler::ProcessOpcode(ud_t ud_obj, int prefix_length,
                    union _restricted_instruction *restricted_instruction) {
  unsigned char *instruction_ptr;
  unsigned char *opcode_ptr;
  int opcode_length;
  unsigned char opcode;

  instruction_ptr = (unsigned char *)ud_insn_ptr(&ud_obj);
  opcode_ptr = instruction_ptr + prefix_length;
  opcode_length = 0;
  if (*opcode_ptr == 0x0f) { // 1st byte of opcode
    switch (*(opcode_ptr + 1)) { // 2nd byte of opcode
      case 0x0d:
      case 0x0f:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x38:
      case 0x3a:
        opcode_length = 3;
        break;
      default:
        opcode_length = 2;
    }
  } else {
    opcode_length = 1;
  }
  if (opcode_length == 1) opcode = *opcode_ptr;
  else if (opcode_length == 2) opcode = *(opcode_ptr + 1);
  else if (opcode_length == 3) opcode = *(opcode_ptr + 2);
  else exit(EXIT_FAILURE);

  if (opcode_length > 1) (*restricted_instruction).byte[0] |= 0x01;
  (*restricted_instruction).byte[1] |= opcode;

  printf("Opcode byte: %x\n", opcode);
  std::cout << "Opcode length: " << opcode_length << std::endl;
  return opcode_length;
}

void Disassembler::ProcessModRMAndSIB(ud_t ud_obj,
                                      int prefix_length,
                                      int opcode_length,
                    union _restricted_instruction *restricted_instruction) {
  const ud_operand_t *operand;
  int operand_count;
  bool does_sib_exists;
  unsigned char modrm;
  unsigned char sib;
  unsigned char *instruction_ptr;
  unsigned char *opcode_ptr;

  does_sib_exists = false;
  operand_count = 0;
  while ((operand = ud_insn_opr(&ud_obj, operand_count)) != NULL) {
    operand_count++;
    if (operand != NULL) {
      if (operand->scale != 0x00) {
        does_sib_exists = true;
      }
    }
  }
  if (operand_count < 2 && does_sib_exists == false) return; // No ModR/M, SIB
  instruction_ptr = (unsigned char *)ud_insn_ptr(&ud_obj);
  opcode_ptr = instruction_ptr + prefix_length;
  if (operand_count >= 2) {
    modrm = *(opcode_ptr + opcode_length);
    (*restricted_instruction).byte[2] |= modrm;
    printf("ModR/M: %x\n", modrm);
  }
  if (does_sib_exists == true) {
    sib = *(opcode_ptr + opcode_length + 1);
    (*restricted_instruction).byte[3] |= sib;
    printf("SIB: %x\n", sib);
  }
}

void Disassembler::DisplayOpcodeFirstByte() {
  // std::cout << "Start displaying..." << std::endl;
  // std::cout << this->base_of_code_ << std::endl;
  // std::cout << this->size_of_code_ << std::endl;
  ud_set_input_buffer(&(this->ud_obj_), this->base_of_code_,
                      this->size_of_code_);
  ud_set_mode(&(this->ud_obj_), 32);
  ud_set_syntax(&(this->ud_obj_), UD_SYN_INTEL);

  while(ud_disassemble(&(this->ud_obj_)) != 0){
    // std::cout << "\t" << std::setw(1) << ud_insn_asm(&(this->ud_obj_)) << std::endl;
    // std::cout << "\t" << std::setw(1) << ud_insn_hex(&(this->ud_obj_)) << std::endl;
    std::string str = ud_insn_hex(&(this->ud_obj_));
    std::cout << str.at(0) << str.at(1) << std::endl;
  }
}

}  // namespace beelzebub
