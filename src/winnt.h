#ifndef BEELZEBUB_WINNT_H_
#define BEELZEBUB_WINNT_H_

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;


typedef struct _IMAGE_FILE_HEADER{
	WORD	Machine;
	WORD	NumberOfSections;
	DWORD	TimeDateStamp;
	DWORD	PointerToDymbolTable;
	DWORD	NumberOfSymbols;
	WORD	SizeOfOptionalHeader;
	WORD	Characeristics;
}IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;


typedef struct _IMAGE_DATA_DIRECTORY{
	DWORD RVA;
	DWORD Size;
}IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;


typedef struct _IMAGE_OPTIONAL_HEADER{
	// Standard fields
	WORD	Magic;
	BYTE	MajorLinkerVersion;
	BYTE	MinorLinkerVersion;
	DWORD	SizeOfCode;
	DWORD	SizeOfInitializedData;
	DWORD	SizeOfUninitializedData;
	DWORD	AddressOfEntryPoint;
	DWORD	BaseOfCode;
	DWORD	BaseOfData;

	// NT additional fields
	DWORD	ImageBase;
	DWORD	SectionAlignment;
	DWORD	FileAlignment;
	WORD	MajorOperatingSystemVersion;
	WORD	MinorOperatingSystemVersion;
	WORD	MajorImageVersion;
	WORD	MinorImageVersion;
	WORD	MajorSubsystemVersion;
	WORD	MinorSubsystemVersion;
	DWORD	Win32VersionValue;
	DWORD	SizeOfImage;
	DWORD	SizeOfHeaders;
	DWORD	CheckSum;
	WORD	Subsystem;
	WORD	DllCharacteristics;
	DWORD	SizeOfStackReserve;
	DWORD	SizeOfStackCommit;
	DWORD	SizeOfHeapReserve;
	DWORD	SizeOfHeapCommit;
	DWORD	LoaderFlags;
	DWORD	NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
}IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;


typedef struct _IMAGE_NT_HEADERS{
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER32 OptionalHeader;
}IMAGE_NT_HEADER32, *PIMAGE_NT_HEADERS32;


typedef struct _IMAGE_IMPORT_DESCRIPTOR{
	union{
		DWORD	Characteristics;
		DWORD	OriginalFirstThunk;
	};
	DWORD	TimeDateStamp;
	DWORD	ForwarderChain;
	DWORD	Name;
	DWORD	FirstThunk;
}IMAGE_IMPORT_DESCRIPTOR, *PIMAGE_IMPORT_DESCRIPTOR;


typedef struct _IMAGE_THUNK_DATA32{
	union{
		DWORD	ForwarderString;
		DWORD	Function;
		DWORD	Ordinal;
		DWORD	AddressOfData;
	}u1;
}IMAGE_THUNK_DATA32, *PIMAGE_THUNK_DATA32;


typedef struct _IMAGE_IMPORT_BY_NAME{
	WORD	Hint;
	BYTE	Name[1];
}IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;

#endif /* BEELZEBUB_WINNT_H_ */
