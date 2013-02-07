#ifndef BEELZEBUB_ANALYZE_H_
#define BEELZEBUB_ANALYZE_H_

#define DEBUG

#include "winnt.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

namespace beelzebub{
	class Analyzer{
		public:
			// Constructor, Destructor
			Analyzer();
			~Analyzer();

			// Accessor, Mutator
			unsigned char *get_code();
			void set_pe_signature_address(unsigned char *signature_address);

			void Read(char *filename, int size);
			void Read(char *filename);
			void Run();

			unsigned char *SearchSignature(unsigned char *signature);
			void SearchPeSignature();
			void GetPeHeader();
			void ShowPeHeader();
			void SearchImportTable();
			void ExtractImageImportDescriptor();
			bool IsEndOfImageImportDescriptorTable(unsigned char *pointer);
			void ExtractDLL();
			void ShowDLL();
			void ExtractAPI();
			void ShowAPI();

		private:
			/* Code */
			unsigned char *code_;
			int code_size_;

			/* PE header */
			unsigned char *pe_signature_address_;
			IMAGE_NT_HEADER32 *pe_header_;

			/* Import Section */
			unsigned char *import_table_address_;
			std::vector<IMAGE_IMPORT_DESCRIPTOR *> image_import_descriptor_;
			int dll_num_;
			std::vector<std::string> DLL;
			std::vector<IMAGE_IMPORT_BY_NAME *> API;

			int GetFileSize(FILE *fp);
	};
}

#endif /* BEELZEBUB_ANALYZE_H_ */
