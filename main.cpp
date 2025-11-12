#include <iostream>
#include <fstream>
#include <sstream>
#include "Compiler.h"
#include "VM/VirtualMachine.h"

int main(int argc, char** argv)
{
    //Check correct usage
    /*
    if (argc < 2) {
        std::cout << "Usage: BrainFucker <filename>";
        return 0;
    }
    */
    //Read source file
    //std::ifstream sourceFile(argv[1]);
    std::ifstream sourceFile("mandelbrot.bf");

    if (!sourceFile.is_open()) {
        std::cerr << "Unable to open source file '" << argv[1] << "'\n";
        return -1;
    }

    std::stringstream fileBuffer;
    fileBuffer << sourceFile.rdbuf();
    const std::string fileString = fileBuffer.str();
    fileBuffer.clear();

    //Compile
    BrainFucker::Compiler compiler;
    auto ops = compiler.Compile(fileString);

    //VM
    BrainFucker::VM::VirtualMachine vm;
    vm.Execute(ops);

    /*
    std::ofstream outfile("out.bfil", std::ios::binary);
    if (outfile.is_open()) {
        for (auto op : ops) {
            outfile << op;
        }
    }
    */
    return 0;
}
