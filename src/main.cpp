#include "GeneratorFactory.h"

#include <iostream>

using macrogen::GeneratorFactory;

int main(int argc, const char * argv[]) {
    std::string input_filepath = "/Users/filip/Desktop/INFA/ECOTE/LABS/macro-gen/macro-gen/data/input.txt";
    std::string output_filepath = "/Users/filip/Desktop/INFA/ECOTE/LABS/macro-gen/macro-gen/data/output.txt";
    std::string exception_filepath = "/Users/filip/Desktop/INFA/ECOTE/LABS/macro-gen/macro-gen/data/exception_output.txt";
    
    std::unique_ptr<macrogen::Generator> generator = GeneratorFactory::createGenerator();
    generator->convert(input_filepath, output_filepath, exception_filepath);
        
    return 0;
}
