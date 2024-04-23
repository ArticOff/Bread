#include "instruction_reader.hpp"

long  double datatoarithmetic(std::vector<data*> &datas, const data* Data);

bool isInt(std::string& input)
{
    try
    {
        std::stoi(input);
        return true;
    }
    catch(const std::exception& err)
    {
        return false;
    }
}

long  double arithmeticvectorreader(std::vector<data*> &datas, std::vector<std::string> calculationstring,bool local);

long  double functionreader(std::vector<data*> &datas, std::vector<std::string> functionstring, std::vector<data *>::iterator &it)
{
    int i = 2;
    std::vector<std::string> insideparenthese;
    std::vector<std::string> argumentfunctionstring;
    for(; i < functionstring.size(); i++)
    {
        if(functionstring[i] == ")" && i == functionstring.size() - 1)
        {
            argumentfunctionstring.push_back(std::to_string(arithmeticvectorreader(datas, insideparenthese, false)));
            insideparenthese.clear();
            break;
        }
        else if(functionstring[i] == ",")
        {
            argumentfunctionstring.push_back(std::to_string(arithmeticvectorreader(datas, insideparenthese, false)));
            insideparenthese.clear();
        }
        else
        {
            insideparenthese.push_back(functionstring[i]);
        }
    }
    data * Type = (*it);
    data * ActualArg = Type->next->next;
    data* type;
    int size = 0;
    for(std::string argument : argumentfunctionstring)
    {
        type = new data("local_variable");
        data* name = new data(ActualArg->dataS);
        data* value = new data(argument);
        type->next = name;
        name->next = value;
        datas.push_back(type);
        ActualArg = ActualArg->next;
        size++;
    }
    
    //get result so we can return
    long  double result = datatoarithmetic(datas, ActualArg);
    
    //free memory of our variables
    
    i = datas.size() - size;
    
    for(; i < datas.size() ; i++)
    {
        //deletes the thing
        data* Data2 = datas[i]->next;
        while (Data2 != nullptr)
        {
            data* Data_temp = Data2;
            Data2 = Data2->next;
            delete Data_temp;
        }
        delete datas[i];
    }
    
    datas.erase(datas.begin() + datas.size() - size, datas.end());
    return result;
}

long  double arithmeticvectorreader(std::vector<data*> &datas, std::vector<std::string> calculationstring, bool local)
{
    int i = 0;
    //check that all parentheses are closed
    int opened_parentheses = 0;
    int closed_parentheses = 0;
    for (std::string element : calculationstring)
    {
        if (element == "(")
        {
            opened_parentheses++;
        }
        else if (element == ")")
        {
            closed_parentheses++;
        }
    }
    if (opened_parentheses != closed_parentheses)
    {
        throw std::runtime_error("parentheses are not all closed");
    }
    //replace var to number
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] != "*" && calculationstring[i] != "**" && calculationstring[i] != "/" && calculationstring[i] != "+" && calculationstring[i] != "-" && calculationstring[i] != "(" && calculationstring[i] != ")"  
        && isInt(calculationstring[i]) == false && calculationstring[i] != "==" && calculationstring[i] != "!=" && calculationstring[i] != ">=" && calculationstring[i] != "<=")
        {
            if(local == false)
            {
                auto it = std::find_if(datas.begin(), datas.end(), name_equals(calculationstring[i]));
                if (it != datas.end())
                {
                    if ((*it)->dataS == "variable")
                    {
                        calculationstring[i] = (*it)->next->next->dataS;
                    }   
                    
                    else if((*it)->dataS != "function")
                    {
                        throw std::runtime_error("undefined variable");
                    }
                }
                else
                {
                    throw std::runtime_error("undefined variable");
                }
            }
            else
            {
                auto it = std::find_if(datas.begin(), datas.end(), [&](const data* ptr) {
                    return name_equals(calculationstring[i])(ptr) && type_equals("local_variable")(ptr);
                });

                if (it != datas.end())
                {
                    calculationstring[i] = (*it)->next->next->dataS;
                }
                else
                {
                    it = std::find_if(datas.begin(), datas.end(), name_equals(calculationstring[i]));
                    if (it != datas.end())
                    {
                        if ((*it)->dataS == "variable")
                        {
                            calculationstring[i] = (*it)->next->next->dataS;
                        }
                        else if((*it)->dataS != "function")
                        {
                            throw std::runtime_error("undefined variable");
                        }
                    }
                    else
                    {
                        throw std::runtime_error("undefined variable");
                    }
                }
            }
        }
    }
    //replace function by number
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] != "*" && calculationstring[i] != "**" && calculationstring[i] != "/" && calculationstring[i] != "+" && calculationstring[i] != "-" && calculationstring[i] != "(" && calculationstring[i] != ")"  
        && isInt(calculationstring[i]) == false && calculationstring[i] != "==" && calculationstring[i] != "!=" && calculationstring[i] != ">=" && calculationstring[i] != "<=")
        {
            auto it = std::find_if(datas.begin(), datas.end(), name_equals(calculationstring[i]));
            if (it != datas.end())
            {
                int stack = 1;
                int i2 = i + 2;
                std::vector<std::string> function;
                function.push_back(calculationstring[i]);
                function.push_back("(");
                for (; i2 < calculationstring.size(); i2++)
                {
                    function.push_back(calculationstring[i2]);
                    if (calculationstring[i2] == ")")
                    {
                        stack--;
                        if (stack == 0)
                        {
                            break;
                        }
                    }
                    if (calculationstring[i2] == "(")
                    {
                        stack++;
                    }
                }
                long  double functionread = functionreader(datas, function, it);
                auto start = calculationstring.begin() + i + 1;
                auto end = calculationstring.begin() + i2 + 1;
                calculationstring.erase(start, end);
                calculationstring[i] = std::to_string(functionread);
            }
            else
            {
                throw std::runtime_error("undefined function");
            }
        }
    }
    //for parentheses in the calculation
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] == "(")
        {
            int stack = 1;
            int i2 = i + 1;
            std::vector<std::string> inparenthesecalculationstring;
            for(; i2 < calculationstring.size() ; i2++)
            {
                if(calculationstring[i2] == ")")
                {
                    stack--;
                    if(stack == 0)
                    {
                        break;
                    }
                }
                if(calculationstring[i2] == "(")
                {
                    stack++;
                }
                inparenthesecalculationstring.push_back(calculationstring[i2]);
            }
            //delete not working, next thing to fix
            auto start = calculationstring.begin() + i + 1;
            auto end = calculationstring.begin() + i2 + 1;
            calculationstring.erase(start, end);
            calculationstring[i] = std::to_string(arithmeticvectorreader(datas, inparenthesecalculationstring, false));
        }
    }
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] == "**" && calculationstring.size() > i + 1)
        {
            long  double result = std::pow(std::stold(calculationstring[i - 1]) , std::stold(calculationstring[i + 1]));
            calculationstring.erase(calculationstring.begin() + i);
            calculationstring.erase(calculationstring.begin() + i);
            i -= 1;
            calculationstring[i] = std::to_string(result);
        }
        else if (calculationstring[i] == "**")
        {
            throw std::runtime_error("invalid operation");
        }
    }
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] == "*" && calculationstring.size() > i + 1)
        {
            long  double result = std::stold(calculationstring[i - 1]) * std::stold(calculationstring[i + 1]);
            calculationstring.erase(calculationstring.begin() + i);
            calculationstring.erase(calculationstring.begin() + i);
            i -= 1;
            calculationstring[i] = std::to_string(result);
        }
        else if (calculationstring[i] == "*")
        {
            throw std::runtime_error("invalid operation");
        }
        else if(calculationstring[i] == "/" && calculationstring.size() > i + 1)
        {
            long  double result = std::stold(calculationstring[i - 1]) / std::stold(calculationstring[i + 1]);
            calculationstring.erase(calculationstring.begin() + i);
            calculationstring.erase(calculationstring.begin() + i);
            i -= 1;
            calculationstring[i] = std::to_string(result);
        }
        else if (calculationstring[i] == "/")
        {
            throw std::runtime_error("invalid operation");
        }
    }
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] == "+")
        {
            if(i != 0)
            {
                if(calculationstring[i - 1] != "*" && calculationstring[i - 1] != "**" && calculationstring[i - 1] != "/" && calculationstring[i - 1] != "+" && calculationstring[i - 1] != "-" && calculationstring.size() > i + 1)
                {
                    long  double result = std::stold(calculationstring[i - 1]) + std::stold(calculationstring[i + 1]);
                    calculationstring.erase(calculationstring.begin() + i);
                    calculationstring.erase(calculationstring.begin() + i);
                    i -= 1;
                    calculationstring[i] = std::to_string(result);
                }
                else if(calculationstring.size() > i + 1)
                {
                    std::string result = "+" + calculationstring[i + 1];
                    calculationstring.erase(calculationstring.begin() + i);
                    calculationstring[i] = result;
                }
                else
                {
                    throw std::runtime_error("invalid operation");
                }
            }
            else if(calculationstring.size() > i + 1)
            {
                std::string result = "+" + calculationstring[i + 1];
                calculationstring.erase(calculationstring.begin() + i);
                calculationstring[i] = result;
            }
            else
            {
                throw std::runtime_error("invalid operation");
            }
        }
        else if(calculationstring[i] == "-")
        {
            if (i != 0)
            {
                if (calculationstring[i - 1] != "*" && calculationstring[i - 1] != "**" && calculationstring[i - 1] != "/" && calculationstring[i - 1] != "+" && calculationstring[i - 1] != "-" && calculationstring.size() > i + 1)
                {
                    long  double result = std::stold(calculationstring[i - 1]) - std::stold(calculationstring[i + 1]);
                    calculationstring.erase(calculationstring.begin() + i);
                    calculationstring.erase(calculationstring.begin() + i);
                    i -= 1;
                    calculationstring[i] = std::to_string(result);
                }
                else if (calculationstring.size() > i + 1)
                {
                    std::string result = "-" + calculationstring[i + 1];
                    calculationstring.erase(calculationstring.begin() + i);
                    calculationstring[i] = result;
                }
                else
                {
                    throw std::runtime_error("invalid operation");
                }
            }
            else if (calculationstring.size() > i + 1)
            {
                std::string result = "-" + calculationstring[i + 1];
                calculationstring.erase(calculationstring.begin() + i);
                calculationstring[i] = result;
            }
            else
            {
                throw std::runtime_error("invalid operation");
            }
        }
    }
    //for condition operators
    i = 0;
    for(; i < calculationstring.size() ; i++)
    {
        if(calculationstring[i] == "==" || calculationstring[i] == "!=" || calculationstring[i] == ">=" || calculationstring[i] == "<=")
        {
            if(calculationstring.size() > i + 1)
            {
                long double result;
                if(calculationstring[i] == "==")
                {
                    if(calculationstring[i - 1] == calculationstring[i + 1])
                    {
                        result = 1;
                    }
                    else
                    {
                        result = 0;
                    }
                }
                else if(calculationstring[i] == "!=")
                {
                    if(calculationstring[i - 1] != calculationstring[i + 1])
                    {
                        result = 1;
                    }
                    else
                    {
                        result = 0;
                    }
                }
                else if(calculationstring[i] == ">=")
                {
                    if(std::stold(calculationstring[i - 1]) >= std::stold(calculationstring[i + 1]))
                    {
                        result = 1;
                    }
                    else
                    {
                        result = 0;
                    }
                }
                else if(calculationstring[i] == "<=")
                {
                    if(std::stold(calculationstring[i - 1]) <= std::stold(calculationstring[i + 1]))
                    {
                        result = 1;
                    }
                    else
                    {
                        result = 0;
                    }
                }
                calculationstring.erase(calculationstring.begin() + i);
                calculationstring.erase(calculationstring.begin() + i);
                i -= 1;
                calculationstring[i] = std::to_string(result);
            }
            else
            {
                throw std::runtime_error("invalid operation");
            }
        }
    }
    if (calculationstring.size() > 1)
    {
        throw std::runtime_error("missing operators");
    }
    return std::stold(calculationstring[0]);
}

long  double instructiontoarithmetic(std::vector<data*> &datas, const instructions* instruction)
{
    std::vector<std::string> calculationstring;
    const instructions * instruction2 = instruction;
    //get the value in the calculation string
    while(instruction2 != nullptr)
    {
        calculationstring.push_back(instruction2->data);
        instruction2 = instruction2->next;
    }
    return arithmeticvectorreader(datas, calculationstring,false);
}

long  double datatoarithmetic(std::vector<data*> &datas, const data* Data)
{
    std::vector<std::string> calculationstring;
    const data * Data2 = Data->next;
    //get the value in the calculation string
    while(Data2 != nullptr)
    {
        calculationstring.push_back(Data2->dataS);
        Data2 = Data2->next;
    }
    return arithmeticvectorreader(datas, calculationstring,true);
}
