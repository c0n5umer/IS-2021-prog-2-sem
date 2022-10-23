//
// Created by Aleksandr Orlov on 25.04.2022.
//

#ifndef LAB4_CUBE_H
#define LAB4_CUBE_H

#define POPULATION_SIZE 500
#define MAX_GENERATIONS 300
#define MAX_RESETS 10
#define ELITISM_NUM 50

#include <vector>
#include <string>
#include <fstream>
#include <random>

// 1 - clockwise, 0 - counter clockwise
void rotate(std::vector<std::vector<char>> &vec, bool direction) {
    std::vector<std::vector<char>> tmp(3, std::vector<char>(3));

    if (direction) {
        for (int i = 0; i < 3; ++i)
            for (int j = 2; j >= 0; --j)
                tmp[i][2 - j] = vec[j][i];
    } else {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                tmp[2 - j][i] = vec[i][j];
    }
    vec = tmp;
}

std::vector<std::string> single_moves = {"U", "U'", "U2", "D", "D'", "D2",
                                         "R", "R'", "R2", "L", "L'", "L2",
                                         "F", "F'", "F2", "B", "B'", "B2"};

std::vector<std::string> full_rotations = {"x", "x'", "x2", "y", "y'", "y2"};

std::vector<std::string> orientations = {"z", "z'", "z2"};

std::vector<std::string> permutations = {"F' L' B' R' U' R U' B L F R U R' U",
                                         "F R B L U L' U B' R' F' L' U' L U'",
                                         "U2 B U2 B' R2 F R' F' U2 F' U2 F R'",
                                         "U2 R U2 R' F2 L F' L' U2 L' U2 L F'",
                                         "U' B2 D2 L' F2 D2 B2 R' U'",
                                         "U B2 D2 R F2 D2 B2 L U",
                                         "D' R' D R2 U' R B2 L U' L' B2 U R2",
                                         "D L D' L2 U L' B2 R' U R B2 U' L2",
                                         "R' U L' U2 R U' L R' U L' U2 R U' L U'",
                                         "L U' R U2 L' U R' L U' R U2 L' U R' U",
                                         "F' U B U' F U B' U'",
                                         "F U' B' U F' U' B U",
                                         "L' U2 L R' F2 R",
                                         "R' U2 R L' B2 L",
                                         "M2 U M2 U2 M2 U M2"};

class Cube {
private:
    std::vector<std::vector<char>> up_;
    std::vector<std::vector<char>> left_;
    std::vector<std::vector<char>> front_;
    std::vector<std::vector<char>> right_;
    std::vector<std::vector<char>> back_;
    std::vector<std::vector<char>> down_;
    int fitness_ = 54;
    std::string solution_ = "";

    // Simple rotations for rotations
    void simpleRotationFRBL(int layer) {
        std::vector<char> f = front_[layer];
        std::vector<char> r = right_[layer];
        std::vector<char> b = back_[layer];
        std::vector<char> l = left_[layer];

        for (int i = 0; i < 3; ++i) {
            right_[layer][i] = f[i];
            back_[layer][i] = r[i];
            left_[layer][i] = b[i];
            front_[layer][i] = l[i];
        }
    }

    void simpleRotationFRBLPrime(int layer) {
        std::vector<char> f = front_[layer];
        std::vector<char> r = right_[layer];
        std::vector<char> b = back_[layer];
        std::vector<char> l = left_[layer];

        for (int i = 0; i < 3; ++i) {
            right_[layer][i] = b[i];
            back_[layer][i] = l[i];
            left_[layer][i] = f[i];
            front_[layer][i] = r[i];
        }
    }

    void simpleRotationFDBU(int layer) {
        std::vector<char> f;
        std::vector<char> d;
        std::vector<char> b;
        std::vector<char> u;

        for (int i = 0; i < 3; ++i) {
            f.emplace_back(front_[i][layer]);
            d.emplace_back(down_[i][layer]);
            b.emplace_back(back_[2 - i][2 - layer]);
            u.emplace_back(up_[i][layer]);
        }

        for (int i = 0; i < 3; ++i) {
            front_[i][layer] = u[i];
            down_[i][layer] = f[i];
            back_[2 - i][2 - layer] = d[i];
            up_[i][layer] = b[i];
        }
    }

    void simpleRotationFDBUPrime(int layer) {
        std::vector<char> f;
        std::vector<char> d;
        std::vector<char> b;
        std::vector<char> u;

        for (int i = 0; i < 3; ++i) {
            f.emplace_back(front_[i][layer]);
            d.emplace_back(down_[i][layer]);
            b.emplace_back(back_[2 - i][2 - layer]);
            u.emplace_back(up_[i][layer]);
        }

        for (int i = 0; i < 3; ++i) {
            front_[i][layer] = d[i];
            down_[i][layer] = b[i];
            back_[2 - i][2 - layer] = u[i];
            up_[i][layer] = f[i];
        }
    }

    void simpleRotationLURD(int layer) {
        std::vector<char> l;
        std::vector<char> u = up_[layer];
        std::vector<char> r;
        std::vector<char> d = down_[2 - layer];

        std::reverse(d.begin(), d.end());
        std::reverse(u.begin(), u.end());

        for (int i = 0; i < 3; ++i) {
            l.emplace_back(left_[i][layer]);
            r.emplace_back(right_[i][2 - layer]);
        }

        for (int i = 0; i < 3; ++i) {
            up_[layer][i] = r[i];
            left_[i][layer] = u[i];
            down_[2 - layer][i] = l[i];
            right_[i][2 - layer] = d[i];
        }
    }

    void simpleRotationLURDPrime(int layer) {
        std::vector<char> l;
        std::vector<char> u = up_[layer];
        std::vector<char> r;
        std::vector<char> d = down_[2 - layer];

        for (int i = 0; i < 3; ++i) {
            l.emplace_back(left_[i][layer]);
            r.emplace_back(right_[i][2 - layer]);
        }

        for (int i = 0; i < 3; ++i) {
            up_[layer][i] = l[2 - i];
            left_[i][layer] = d[i];
            down_[2 - layer][i] = r[2 - i];
            right_[i][2 - layer] = u[i];
        }
    }

    // True random moves
    void rndSingleMove() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, single_moves.size() - 1);
        execute(single_moves[distrib(gen)]);
    }

    void rndPermutation() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, permutations.size() - 1);
        execute(permutations[distrib(gen)]);
    }

    void rndFullRotation() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, full_rotations.size() - 1);
        execute(full_rotations[distrib(gen)]);
    }

    void rndOrientation() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, orientations.size() - 1);
        execute(orientations[distrib(gen)]);
    }
public:
    Cube() {
        up_.resize(3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                up_[i].emplace_back('W');

        left_.resize(3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                left_[i].emplace_back('O');

        front_.resize(3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                front_[i].emplace_back('G');

        right_.resize(3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                right_[i].emplace_back('R');

        back_.resize(3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                back_[i].emplace_back('B');

        down_.resize(3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                down_[i].emplace_back('Y');

        fitness_ = 0;
    }

    Cube(const Cube &cube) {
        up_ = cube.up_;
        left_ = cube.left_;
        front_ = cube.front_;
        right_ = cube.right_;
        back_ = cube.back_;
        down_ = cube.down_;
        fitness_ = cube.fitness_;
        solution_ = cube.solution_;
    }

    Cube(const std::string &filename) {
        std::ifstream myFile;
        myFile.open(filename, std::ofstream::in);

        up_.resize(3);
        for (int i = 0; i < 9; ++i) {
            char symb;

            myFile >> symb;
            up_[i / 3].emplace_back(symb);
        }

        left_.resize(3);
        for (int i = 0; i < 9; ++i) {
            char symb;

            myFile >> symb;
            left_[i / 3].emplace_back(symb);
        }

        front_.resize(3);
        for (int i = 0; i < 9; ++i) {
            char symb;

            myFile >> symb;
            front_[i / 3].emplace_back(symb);
        }

        right_.resize(3);
        for (int i = 0; i < 9; ++i) {
            char symb;

            myFile >> symb;
            right_[i / 3].emplace_back(symb);
        }

        back_.resize(3);
        for (int i = 0; i < 9; ++i) {
            char symb;

            myFile >> symb;
            back_[i / 3].emplace_back(symb);
        }

        down_.resize(3);
        for (int i = 0; i < 9; ++i) {
            char symb;

            myFile >> symb;
            down_[i / 3].emplace_back(symb);
        }
        calculateFitness();
        myFile.close();
    }

    Cube &operator=(const Cube &cube) {
        up_ = cube.up_;
        left_ = cube.left_;
        front_ = cube.front_;
        right_ = cube.right_;
        back_ = cube.back_;
        down_ = cube.down_;
        fitness_ = cube.fitness_;
        solution_ = cube.solution_;
        return *this;
    }

    void print(std::ostream &stream) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                stream << up_[i][j] << " ";
            stream << "\n";
        }
        stream << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                stream << left_[i][j] << " ";
            stream << "\n";
        }
        stream << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                stream << front_[i][j] << " ";
            stream << "\n";
        }
        stream << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                stream << right_[i][j] << " ";
            stream << "\n";
        }
        stream << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                stream << back_[i][j] << " ";
            stream << "\n";
        }
        stream << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                stream << down_[i][j] << " ";
            stream << "\n";
        }
        stream << "\n";
    }

    void print(const std::string &filename) const {
        std::ofstream myFile(filename);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                myFile << up_[i][j] << " ";
            myFile << "\n";
        }
        myFile << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                myFile << left_[i][j] << " ";
            myFile << "\n";
        }
        myFile << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                myFile << front_[i][j] << " ";
            myFile << "\n";
        }
        myFile << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                myFile << right_[i][j] << " ";
            myFile << "\n";
        }
        myFile << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                myFile << back_[i][j] << " ";
            myFile << "\n";
        }
        myFile << "\n";

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                myFile << down_[i][j] << " ";
            myFile << "\n";
        }
        myFile << "\n";

        myFile.close();
    }

    friend std::ostream &operator<<(std::ostream &stream, const Cube &cube) {
        cube.print(stream);
        return stream;
    }

    // Operators for sort()
    bool operator==(const Cube &cube) const {
        if (cube.fitness_ == fitness_)
            return true;
        return false;
    }

    bool operator!=(const Cube &cube) const {
        if (*this == cube)
            return false;
        return true;
    }

    bool operator<(const Cube &cube) const {
        if (fitness_ < cube.fitness_)
            return true;
        return false;
    }

    bool operator>(const Cube &cube) const {
        if (fitness_ > cube.fitness_)
            return true;
        return false;
    }

    bool operator<=(const Cube &cube) const {
        if (*this < cube || *this == cube)
            return true;
        return false;
    }

    bool operator>=(const Cube &cube) const {
        if (*this > cube || *this == cube)
            return true;
        return false;
    }

    // Rotations
    void D() {
        rotate(down_, 1);
        simpleRotationFRBL(2);
    }

    void D_prime() {
        rotate(down_, 0);
        simpleRotationFRBLPrime(2);
    }

    void D2() {
        D();
        D();
    }

    void E() {
        simpleRotationFRBL(1);
    }

    void E_prime() {
        simpleRotationFRBLPrime(1);
    }

    void E2() {
        E();
        E();
    }

    void U() {
        rotate(up_, 1);
        simpleRotationFRBLPrime(0);
    }

    void U_prime() {
        rotate(up_, 0);
        simpleRotationFRBL(0);
    }

    void U2() {
        U();
        U();
    }

    void L() {
        rotate(left_, 1);
        simpleRotationFDBU(0);
    }

    void L_prime() {
        rotate(left_, 0);
        simpleRotationFDBUPrime(0);
    }

    void L2() {
        L();
        L();
    }

    void R() {
        rotate(right_, 1);
        simpleRotationFDBUPrime(2);
    }

    void R_prime() {
        rotate(right_, 0);
        simpleRotationFDBU(2);
    }

    void R2() {
        R();
        R();
    }

    void M() {
        simpleRotationFDBU(1);
    }

    void M_prime() {
        simpleRotationFDBUPrime(1);
    }

    void M2() {
        M();
        M();
    }

    void B() {
        rotate(back_, 1);
        simpleRotationLURD(0);
    }

    void B_prime() {
        rotate(back_, 0);
        simpleRotationLURDPrime(0);
    }

    void B2() {
        B();
        B();
    }

    void F() {
        rotate(front_, 1);
        simpleRotationLURDPrime(2);
    }

    void F_prime() {
        rotate(front_, 0);
        simpleRotationLURD(2);
    }

    void F2() {
        F();
        F();
    }

    void S() {
        simpleRotationLURDPrime(1);
    }

    void S_prime() {
        simpleRotationLURD(1);
    }

    void S2() {
        S();
        S();
    }

    void x() {
        L_prime();
        M_prime();
        R();
    }

    void x_prime() {
        L();
        M();
        R_prime();
    }

    void x2() {
        x();
        x();
    }

    void y() {
        U();
        E_prime();
        D_prime();
    }

    void y_prime() {
        U_prime();
        E();
        D();
    }

    void y2() {
        y();
        y();
    }

    void z() {
        F();
        S();
        B_prime();
    }

    void z_prime() {
        F_prime();
        S_prime();
        B();
    }

    void z2() {
        z();
        z();
    }

    // Executes the string with some rotations
    void execute(const std::string &str) {
        std::vector<std::string> v;
        std::string temp = "";

        // Splitting the string
        for (int i = 0; i < str.length(); ++i) {

            if (str[i] == ' ') {
                v.push_back(temp);
                temp = "";
            } else
                temp.push_back(str[i]);
        }
        v.push_back(temp);

        for (int i = 0; i < v.size(); ++i) {
            std::string cmd = v[i];

            if (cmd == "D")
                D();
            else if (cmd == "D'")
                D_prime();
            else if (cmd == "D2")
                D2();
            else if (cmd == "E")
                E();
            else if (cmd == "E'")
                E_prime();
            else if (cmd == "E2")
                E2();
            else if (cmd == "U")
                U();
            else if (cmd == "U'")
                U_prime();
            else if (cmd == "U2")
                U2();
            else if (cmd == "L")
                L();
            else if (cmd == "L'")
                L_prime();
            else if (cmd == "L2")
                L2();
            else if (cmd == "R")
                R();
            else if (cmd == "R'")
                R_prime();
            else if (cmd == "R2")
                R2();
            else if (cmd == "M")
                M();
            else if (cmd == "M'")
                M_prime();
            else if (cmd == "M2")
                M2();
            else if (cmd == "B")
                B();
            else if (cmd == "B'")
                B_prime();
            else if (cmd == "B2")
                B2();
            else if (cmd == "F")
                F();
            else if (cmd == "F'")
                F_prime();
            else if (cmd == "F2")
                F2();
            else if (cmd == "S")
                S();
            else if (cmd == "S'")
                S_prime();
            else if (cmd == "S2")
                S2();
            else if (cmd == "x")
                x();
            else if (cmd == "x'")
                x_prime();
            else if (cmd == "x2")
                x2();
            else if (cmd == "y")
                y();
            else if (cmd == "y'")
                y_prime();
            else if (cmd == "y2")
                y2();
            else if (cmd == "z")
                z();
            else if (cmd == "z'")
                z_prime();
            else if (cmd == "z2")
                z2();
            else throw std::invalid_argument("Incorrect command");

            solution_.append(cmd);
            solution_.append(" ");
        }
        calculateFitness();
    }

    void calculateFitness() {
        int misplaced_stickers = 0;
        char center;

        center = up_[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (up_[i][j] != center)
                    ++misplaced_stickers;

        center = left_[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (left_[i][j] != center)
                    ++misplaced_stickers;

        center = front_[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (front_[i][j] != center)
                    ++misplaced_stickers;

        center = right_[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (right_[i][j] != center)
                    ++misplaced_stickers;

        center = back_[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (back_[i][j] != center)
                    ++misplaced_stickers;

        center = down_[1][1];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (down_[i][j] != center)
                    ++misplaced_stickers;

        fitness_ = misplaced_stickers;
    }

    bool isSolved() {
        if (fitness_ == 0)
            return true;
        return false;
    }

    std::string getSolution() {
        return solution_;
    }

    // GenAlgo
    bool solve() {
        calculateFitness();
        solution_ = "";

        for (int r = 0; r < MAX_RESETS; ++r) {
            std::vector<Cube> cubes;

            // Creating population
            for (int i = 0; i < POPULATION_SIZE; ++i) {
                Cube cube(*this);

                cube.rndSingleMove();
                cube.rndSingleMove();
                cube.calculateFitness();
                cubes.emplace_back(cube);
            }

            // Evolve population
            for (int g = 0; g < MAX_GENERATIONS; ++g) {
                std::sort(cubes.begin(), cubes.end());

                // Trying to find the solution
                for (int i = 0; i < cubes.size(); ++i) {
                    if (cubes[i].isSolved()) {
                        *this = cubes[i];
                        return true;
                    }

                    // Getting the worst in the population cubes
                    if (i >= ELITISM_NUM) {
                        // Getting random cube from the best cubes
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distrib(0, ELITISM_NUM - 1);
                        cubes[i] = cubes[distrib(gen)];

                        std::uniform_int_distribution<> distrib2(0, 5);
                        int evolution_type = distrib2(gen);

                        if (evolution_type == 0)
                            cubes[i].rndPermutation();
                        else if (evolution_type == 1) {
                            cubes[i].rndPermutation();
                            cubes[i].rndPermutation();
                        } else if (evolution_type == 2) {
                            cubes[i].rndFullRotation();
                            cubes[i].rndPermutation();
                        } else if (evolution_type == 3) {
                            cubes[i].rndOrientation();
                            cubes[i].rndPermutation();
                        } else if (evolution_type == 4) {
                            cubes[i].rndFullRotation();
                            cubes[i].rndOrientation();
                            cubes[i].rndPermutation();
                        } else if (evolution_type == 5) {
                            cubes[i].rndOrientation();
                            cubes[i].rndFullRotation();
                            cubes[i].rndPermutation();
                        }
                    }
                }
            }
        }
        return false;
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(20, 40);

        for (int i = 0; i < distrib(gen); ++i)
            rndSingleMove();
    }
};

#endif //LAB4_CUBE_H
