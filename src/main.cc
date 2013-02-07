#include "main.h"

int main(int argc, char **argv){
	char *malware_name;

	malware_name = argv[1];

	beelzebub::Analyzer *analyzer;

	if(argc != 2){
		std::cerr << "Usage: beelzebub (malware file name)" << std::endl;
		exit(EXIT_FAILURE);
	}

	analyzer = new beelzebub::Analyzer;

	analyzer->Read(malware_name, 100000);
	analyzer->Run();

	delete analyzer;

	return 0;
}
