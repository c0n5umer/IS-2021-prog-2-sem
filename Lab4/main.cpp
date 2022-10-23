// Test routes to files
#define INPUT /Users/aleksandrorlov/ITMO/Orlov-Aleksandr/Lab4/input.txt
#define  OUTPUT /Users/aleksandrorlov/ITMO/Orlov-Aleksandr/Lab4/output.txt

#include <iostream>
#include <string>
#include "cube.h"

int main() {
    std::cout << ">>> ";
    Cube cube;

    while (true) {
        std::string in;

        std::cin >> in;

        if (in == "load") {
            std::string fn;

            std::cout << "Enter filename: ";
            std::cin >> fn;

            Cube tmp(fn);
            cube = tmp;
            std::cout << ">>> ";
        } else if (in == "save") {
            std::string fn;

            std::cout << "Enter filename: ";
            std::cin >> fn;

            cube.print(fn);
            std::cout << ">>> ";
        } else if (in == "shuffle") {
            cube.shuffle();
            std::cout << ">>> ";
        } else if (in == "execute") {
            Cube tmp(cube);
            std::string cmd;

            std::cout << "Enter your commands: ";
            std::cin.ignore();
            std::getline(std::cin, cmd);
            try {
                cube.execute(cmd);
            }
            catch(const std::exception& ex) {
                std::cout << "Incorrect rotation\n";
                cube = tmp;
            }
            std::cout << ">>> ";
        } else if (in == "solve") {
            if (cube.solve())
                std::cout << "Solution: " << cube.getSolution() << "\n";
            else
                std::cout << "Incorrect cube\n";
            std::cout << ">>> ";
        } else if (in == "help") {
            std::cout << "save - to save cube in file\nload - to load cube from file\nshuffle - to shuffle cube\n" <<
            "execute - to execute the string of commands\nsolve - to find the solution of cube if it is correct\n" <<
            "print - to the cube in  console\nexit - to exit from the application\n>>> ";
        } else if (in == "print") {
            std::cout << cube;
            std::cout << ">>> ";
        } else if (in == "exit")
            return 0;
        else
            std::cout << "Incorrect command. Try help\n>>> ";
    }
    return 0;
}
