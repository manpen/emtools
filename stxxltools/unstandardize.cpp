#include <iostream>
#include <fstream>
using namespace std;

size_t filesize( const char*const filepath ){
	std::ifstream file(filepath, std::ios::binary | std::ios::ate | std::ios::in);
	if(!file.good()) return 0;
	return file.tellg();
}
bool file_exists(const char *const filepath) {
	std::ifstream infile(filepath);
		return infile.good();
}

int main(int argc, char** argv) {
	if(argc != 2) {
		cout << "Usage: " << argv[0] << " text-file" << std::endl;
		return 1;
	}
	const std::string textfilename = argv[1];
	const std::string Ztextfilename = textfilename + ".1";
	if(!file_exists(textfilename.c_str())) {
		cout << "Could not open text file " << textfilename << std::endl;
		return 1;
	}
	std::ifstream is(textfilename, std::ios::binary);
	std::ofstream os(Ztextfilename, std::ios::binary);
	while(is.good() && !is.eof()) {
		unsigned char c = is.get();
		if(c == static_cast<unsigned char>(std::char_traits<char>::eof())) break;
		if(c == 254) {
			c = is.get();
			if(c == 254)    os << static_cast<char>(254);
			else if(c == 1) os << static_cast<char>(255);
			else if(c == 2) os << static_cast<char>(0);
		}
		else if(c == 0) {
			return 0;
		}
		else {
			os << c;
		}

	}
}
