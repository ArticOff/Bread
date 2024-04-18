#ifndef BREAD_H
#define BREAD_H

#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <filesystem>
#include <regex>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <sstream>

//structs
struct Token { //struct
    std::string type;
    std::string value;
};

struct instructions { //struct
    std::string data;
    int line;
    instructions* next;

    instructions(std::string dataValue) : data(dataValue), next(nullptr), line(-1) {}
};

struct data { //same than instructions but for data and repair in code
    std::string dataS;
    data* next;

    data(std::string dataValue) : dataS(dataValue), next(nullptr) {}
};

//methods
void freememory_instructions(std::vector<instructions*>& instructions_vector);

void freememory_datas(std::vector<data*>& datas_vector);

//tokenize declaration
std::vector<std::vector<Token>> tokenize(const std::string& code, bool debug);

//parser declaration
std::vector<instructions *> parse(std::vector<std::vector<Token>> tokens_lines);

//execute declaration
std::vector<data *> execute(std::vector<instructions*>& instructions_vector);

#endif