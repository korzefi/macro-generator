#include "FileHandler.h"
#include <iostream>

namespace macrogen {

FileHandler::FileHandler(std::unique_ptr<FileParser> parser) : parser(std::move(parser)) {}

data_type FileHandler::readData(const std::string& input_filepath) {
    readRawFile(input_filepath);
    parse();
    return parsed_macros;
}

void FileHandler::readRawFile(const std::string& input_filepath) {
    std::ifstream ifs;
    ifs.open(input_filepath, std::ifstream::in);
    if (not ifs.is_open()) {
        std::cout << "File has not been opened properly" << std::endl;
        exit(1);
    }
    raw_macros = readLines(ifs);
    ifs.close();
}

std::string FileHandler::readLines(std::ifstream& ifs) {
    std::string result;
    std::string line;
    while (std::getline(ifs, line)) {
        result += line;
        result += "\n";
    }
    return result;
}

void FileHandler::parse() {
    parsed_macros = parser->parse(raw_macros);
}

void FileHandler::writeData(const std::string& filepath, std::vector<std::string> output) {
    std::ofstream ofs;
    ofs.open(filepath, std::ofstream::out);
    if (not ofs.is_open()) {
        std::cout << "File has not been opened properly" << std::endl;
        exit(2);
    }
    saveResults(ofs, output);
    ofs.close();
}

void FileHandler::saveResults(std::ofstream& ofs, const std::vector<std::string>& output) {
    for (const auto& macro_output : output) {
        ofs << macro_output;
        ofs << "\n\n";
    }
}

} //namespace macrogen



