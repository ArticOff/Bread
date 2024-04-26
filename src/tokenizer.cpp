#include "../include/bread.hpp"

std::vector<std::vector<Token>> tokenize(const std::string& code, bool debug)
{
    std::vector<std::vector<Token>> tokenslines;
    std::vector<Token> tokens;
    //lexic
    std::string syntax =
    "("
    ">=|<=|==|!=|<|>|" // //condition_operator
    "\\[|\\]|\\(|\\)|;|,|" // separator
    "=|->|:|" // assignation
    "\\+|\\-|/|\\*\\*|\\*|%|" // simple_operator
    "\n|" //jump of line
    "([^\\s\\+\\-*/%><=!\\[\\]\\(\\);,:\n]+)|" // anyword and detect if there is an operator
    "(\\d+(\\.\\d+)?)|"
    "use|print|input" // method
    ")";


    std::regex syntax_pattern(syntax);
    std::smatch match;
    std::string::const_iterator search_start(code.cbegin());
    bool last_n = false;
    while (std::regex_search(search_start, code.cend(), match, syntax_pattern)) 
    {
        if (match.empty()) 
        {
            break;
        }
        else if(match.str() == "\n")
        {
            tokenslines.push_back(tokens);
            tokens.clear();
        }

        else if(match.str() == "[" || match.str() == "]" || match.str() == "(" || match.str() == ")" || match.str() == ";" || match.str() == ",") //separator
        {
            Token token;
            token.type = "separator";
            token.value = match.str();
            tokens.push_back(token);
        }
        
        else if(match.str() == "=" || match.str() == "->" || match.str() == ":") //assignation
        {
            Token token;
            token.type = "assignation";
            token.value = match.str();
            tokens.push_back(token);
        }
        
        else if(match.str() == "print" || match.str() == "input" || match.str() == "use") //method
        {
            Token token;
            token.type = "method";
            token.value = match.str();
            tokens.push_back(token);
        }
        
        else if(match.str() == "+" || match.str() == "-" || match.str() == "/" || match.str() == "**" || match.str() == "*" || match.str() == "%") //simple_operator
        {
            Token token;
            token.type = "simple_operator";
            token.value = match.str();
            tokens.push_back(token);
        }
        
        else if(match.str() == "==" || match.str() == "!=" || match.str() == ">=" || match.str() == "<=" 
        || match.str() == ">" || match.str() == "<") //condition_operator
        {
            Token token;
            token.type = "condition_operator";
            token.value = match.str();
            tokens.push_back(token);
        }

        else if(match.str(), std::regex_match(match.str(), std::regex("-?\\d+(\\.\\d+)?"))) //number
        {
            Token token;
            token.type = "number";
            token.value = match.str();
            tokens.push_back(token);
        }

        else //other
        {
            Token token;
            token.type = "other";
            token.value = match.str();
            tokens.push_back(token);
        }
        search_start = match.suffix().first;
    }
    tokenslines.push_back(tokens);
    if(debug == true)
    {
        int i = 0;
        for(; i < tokenslines.size() ; i++)
        {
            for(const Token token : tokenslines[i])
            {
                std::cout << "type " << token.type << " value " << token.value << " line " << i << std::endl;
            }
        }
    }
    tokens.clear();
    return tokenslines;
}
