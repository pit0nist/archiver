#include "help.h"
#include <iostream>
#include "ostream"

Help::Help() {
    std::cerr << "For compression use: archive -c ARCHIVE_NAME [file1, file2,...]" << std::endl;
    std::cerr << "For decompression use: archive -d ARCHIVE_NAME" << std::endl;
    std::cerr << "For getting this note use: archive -h" << std::endl;
}