#include "instruction_maker.hpp"

std::vector<instructions *> parse(std::vector<std::vector<Token>> tokens_lines)
{
    std::vector<instructions *> instructions_vector;
    int instructionid = -1;
    int linetokenid = 0;
    int line_number = 1;
    for(std::vector<Token>& line_tokens : tokens_lines)
    {
        for(const Token& token : line_tokens)
        {
            if(token.type == "separator")
            {
                if(token.value == "(" || token.value == ")" || token.value == "[" || token.value == "]")
                {
                    who_equal_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
                }
                else if(token.value == ",")
                {
                    who_equal_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
                }
            }
        
            else if(token.type == "assignation")
            {
                if(token.value == "=")
                {   
                    equal_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
                }
            }
        
            else if(token.type == "method")
            {
                if(token.value == "print")
                {
                    method_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
                }
            }
            else if(token.type == "simple_operator")
            {
                who_equal_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
            }
            /*/else if(token.type == "condition_operator")
            {
            
            }/*/
            else if(token.type == "number")
            {
                who_equal_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
            }
            else if (token.type == "other")
            {
                if (linetokenid != 0)
                {
                    who_equal_function(instructions_vector, instructionid, line_tokens, token, linetokenid, line_number);
                }
                else if (line_tokens.size() > 1)
                {
                    if (line_tokens[linetokenid + 1].value == "[")
                    {

                    }
                    if (line_tokens[linetokenid + 1].value == "(")
                    {
                        equal_function_for_function(instructions_vector, instructionid, line_tokens, token, linetokenid);
                    }
                    else if (line_tokens[linetokenid + 1].value != "=")
                    {
                        freememory_instructions(instructions_vector);
                        std::string string_line_number;
                        std::stringstream converting;
                        converting << line_number;
                        throw std::runtime_error("missing declaration at line " + converting.str());
                    }
                }
                else
                {
                    freememory_instructions(instructions_vector);
                    std::string string_line_number;
                    std::stringstream converting;
                    converting << line_number;
                    throw std::runtime_error("no context at line " + converting.str());
                }
            }
            linetokenid++;
        }    
        linetokenid = 0;
        line_number++;
    }
    return instructions_vector;
}