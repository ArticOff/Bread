#include "instruction_maker.hpp"

void equal_function_for_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid)
{

    instructions* Main = new instructions("");
    instructions* type = new instructions("function");
    instructions* whoequalto = new instructions(token.value);
    Main->next = type;
    type->next = whoequalto;
    instructions_vector.push_back(Main);
    instructionid++;
}

void equal_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid, int line_number)
{
    if(linetokenid > 0 && line_tokens[0].type == "other" &&
        line_tokens.size() > linetokenid)
    {
        //for variable
        if(linetokenid == 1)
        {
            instructions* Main = new instructions("=");
            instructions* type = new instructions("variable");
            instructions* whoequalto = new instructions(line_tokens[linetokenid - 1].value);
            Main->next = type;
            type->next = whoequalto;
            Main->line = line_number;
            instructions_vector.push_back(Main);
            instructionid++;
        }
        else if(instructionid >= 0)
        {
            auto instruction_element = instructions_vector[instructionid];
            instruction_element->data = "=";
            instruction_element->line = line_number;
        }
        else
        {
            freememory_instructions(instructions_vector);
            std::string string_line_number;
            std::stringstream converting;
            converting << line_number;
            throw std::runtime_error("not correctly assigned at line " + converting.str());
        }
    }
    else
    {
        freememory_instructions(instructions_vector);
        std::string string_line_number;
        std::stringstream converting;
        converting << line_number;
        throw std::runtime_error("not correctly assigned at line " + converting.str());
    }
}

void who_equal_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid, int line_number)
{
    if(instructionid >= 0)
    {
        auto instruction_element = instructions_vector[instructionid];
        while(instruction_element->next != nullptr)
        {
            instruction_element = instruction_element->next;
        }
        instructions* equalto = new instructions(token.value);
        instruction_element->next = equalto;
    }
    else
    {
        freememory_instructions(instructions_vector);
        std::string string_line_number;
        std::stringstream converting;
        converting << line_number;
        throw std::runtime_error("missing declaration at line " + converting.str());
    }
}


void method_function(std::vector<instructions *> &instructions_vector,int &instructionid, 
std::vector<Token> &line_tokens, const Token &token, int &linetokenid, int line_number)
{
    instructions* Main = new instructions(token.value);
    Main->line = line_number;
    instructions_vector.push_back(Main);
    instructionid++;
}