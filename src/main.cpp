#include "../include/bread.hpp"

int main(int argc, char* argv[])
{
    if(argv[1] != nullptr) //if the second argument is not null
    {
        std::string File = static_cast<std::string>(argv[1]);
        
        std::filesystem::path pathObj(argv[1]);

        std::string extension = pathObj.extension().string();
        
        if(extension == ".brd")
        {
            if(std::filesystem::exists(File))
            {
                std::ifstream t(File);
                std::string textinfile((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
                std::vector<std::vector<Token>> tokens_vector;
                if(argv[2] != nullptr)
                {
                    if(strcmp(argv[2], "-debug") == 0)
                    {
                        tokens_vector = tokenize(textinfile, true);
                    }
                    else
                    {
                        tokens_vector = tokenize(textinfile, false);
                    }
                }
                else
                {
                    tokens_vector = tokenize(textinfile, false);
                }
                try
                {
                    auto instructions_vector = parse(tokens_vector);
                    auto datas = execute(instructions_vector);
                    freememory_datas(datas);
                    freememory_instructions(instructions_vector);
                }
                catch (const std::runtime_error& e)
                {
                    std::cerr << "Fatal error: " << e.what() << std::endl;
                }
            }
            else
            {
                std::cout << "The file doesn't exist." << std::endl;
            }
            }
        else
        {
            std::cout << "The file doesn't have the correct extension, the correct is .bread" << std::endl;
        }
        
    }
    else
    {
        std::cout << "Please enter a file name." << std::endl;
    }

    return 0;
}