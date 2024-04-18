#include "../include/bread.hpp"

void freememory_instructions(std::vector<instructions*>& instructions_vector)
{
    for (instructions* instruction : instructions_vector)
    {
        instructions* instruction2 = instruction->next;
        while (instruction2 != nullptr)
        {
            instructions* instruction_temp = instruction2;
            instruction2 = instruction2->next;
            delete instruction_temp;
        }
        delete instruction;
    }
}
void freememory_datas(std::vector<data*>& datas_vector)
{
    for (const data* Data : datas_vector)
    {
        //deletes the thing
        data* Data2 = Data->next;
        while (Data2 != nullptr)
        {
            data* Data_temp = Data2;
            Data2 = Data2->next;
            delete Data_temp;
        }
        delete Data;
    }
}