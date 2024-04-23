#include "instruction_reader.hpp"

std::vector<data *> execute(std::vector<instructions*>& instructions_vector)
{
    std::vector<data*> datas;
    for(const instructions* instruction : instructions_vector)
    {
        //manage the thing
        if(instruction->data == "=")
        {
            auto it = std::find_if(datas.begin(), datas.end(), name_equals(instruction->next->next->data));
            if(it != datas.end())
            {
                if((*it)->dataS == "variable" && instruction->next->data == "variable")
                {
                    instructions * instruction_to_arithmetic = instruction->next->next->next;
                    long double result = instructiontoarithmetic(datas, instruction_to_arithmetic);
                    (*it)->next->next->dataS = std::to_string(result);
                }
                else if((*it)->dataS == "function" && instruction->next->data == "function")
                {
                    freememory_datas(datas);
                    freememory_instructions(instructions_vector);
                    throw std::runtime_error("can't reassign function");
                }
                else
                {
                    freememory_datas(datas);
                    freememory_instructions(instructions_vector);
                    throw std::runtime_error("can't change a no variable to variable");
                }
            }
            else
            {
                if(instruction->next->data == "variable")
                {
                    instructions * instruction_to_arithmetic = instruction->next->next->next;
                    try
                    {
                        long double result = instructiontoarithmetic(datas, instruction_to_arithmetic);
                        data* type = new data("variable");
                        data* name = new data(instruction->next->next->data);
                        data* value = new data(std::to_string(result));
                        type->next = name;
                        name->next = value;
                        datas.push_back(type);
                    }
                    catch (const std::exception& e)
                    {
                        std::string exception = e.what();
                        std::string string_line_number;
                        std::stringstream converting;
                        converting << instruction->line;
                        freememory_datas(datas);
                        freememory_instructions(instructions_vector);
                        throw std::runtime_error("exception occured at line " + converting.str() + ": " + exception);
                    }
                    catch (const std::runtime_error& e)
                    {
                        std::string exception = e.what();
                        std::string string_line_number;
                        std::stringstream converting;
                        converting << instruction->line;
                        freememory_datas(datas);
                        freememory_instructions(instructions_vector);
                        throw std::runtime_error("error occured at line " + converting.str() + ": " + exception);
                    }
                }
                else if(instruction->next->data == "function")
                {
                    data* type = new data("function");
                    instructions* instruction2 = instruction->next->next;
                    data* thing_for_loop = nullptr;
                    instructions* current_instruction = instruction2;

                    while(current_instruction != nullptr) 
                    {
                        if (thing_for_loop == nullptr) 
                        {
                            if(current_instruction->data != "(" && current_instruction->data != ",") 
                            {
                                if(current_instruction->data != ")") 
                                {
                                    thing_for_loop = new data(current_instruction->data);
                                } 
                                else 
                                {
                                    thing_for_loop = new data(":");
                                    current_instruction = current_instruction->next;
                                    while(current_instruction != nullptr)
                                    {
                                        thing_for_loop->next = new data(current_instruction->data);
                                        thing_for_loop = thing_for_loop->next;
                                        current_instruction = current_instruction->next;
                                    }
                                    break;
                                }
                                type->next = thing_for_loop;
                            }
                        } 
                        else 
                        {
                            if(current_instruction->next != nullptr && current_instruction->next->data != "(" && current_instruction->next->data != ",") 
                            {
                                if(current_instruction->next->data != ")") 
                                {
                                    thing_for_loop->next = new data(current_instruction->next->data);
                                } 
                                else 
                                {
                                    thing_for_loop->next = new data(":");
                                    current_instruction = current_instruction->next->next;
                                    while(current_instruction != nullptr)
                                    {
                                        thing_for_loop->next->next = new data(current_instruction->data);
                                        thing_for_loop = thing_for_loop->next;
                                        current_instruction = current_instruction->next;
                                    }
                                    break;
                                }
                                thing_for_loop = thing_for_loop->next;
                                //std::cout << thing_for_loop->dataS << std::endl;
                            }
                        }
                        current_instruction = current_instruction->next;
                    }
                    /*/data* test = type;
                    while(test != nullptr)
                    {
                        std::cout << test->dataS << std::endl;
                        test = test->next;
                    }/*/
                    datas.push_back(type);
                }
            }
        }
        else if(instruction->data == "print")
        {
            instructions * instruction_to_arithmetic = instruction->next;
            if (instruction_to_arithmetic != nullptr)
            {
                try
                {
                    long  double result = instructiontoarithmetic(datas, instruction_to_arithmetic);
                    std::cout << std::setprecision(std::numeric_limits<long  double>::digits10 + 1)  << result << std::endl;
                }
                catch (const std::exception& e)
                {
                    std::string exception = e.what();
                    std::string string_line_number;
                    std::stringstream converting;
                    converting << instruction->line;
                    freememory_datas(datas);
                    freememory_instructions(instructions_vector);
                    throw std::runtime_error("exception occured at line " + converting.str() + ": " + exception);
                }
                catch (const std::runtime_error& e)
                {
                    std::string exception = e.what();
                    std::string string_line_number;
                    std::stringstream converting;
                    converting << instruction->line;
                    freememory_datas(datas);
                    freememory_instructions(instructions_vector);
                    throw std::runtime_error("error occured at line " + converting.str() + ": " + exception);
                }
            }
            else
            {
                std::stringstream converting;
                converting << instruction->line;
                freememory_datas(datas);
                freememory_instructions(instructions_vector);
                throw std::runtime_error("trying to print none at line " + converting.str());
            }
        }
    }
    return datas;
}
