#include "../../include/bread.hpp"
#ifndef INSTRUCTIONMAKER_H
#define INSTRUCTIONMAKER_H

void equal_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid, int line_number);

void who_equal_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid, int line_number);

void equal_function_for_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid);

void method_function(std::vector<instructions*>& instructions_vector, int& instructionid,
std::vector<Token>& line_tokens, const Token& token, int& linetokenid, int line_number);

#endif