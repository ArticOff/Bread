#include "../../include/bread.hpp"
#ifndef INSTRUCTIONREADER_H
#define INSTRUCTIONREADER_H

struct name_equals {
    name_equals(const std::string& name) : m_name(name) {}
    bool operator()(const data* ptr) const {
        return ptr && ptr->next->dataS == m_name;
    }
    std::string m_name;
};
struct type_equals {
    type_equals(const std::string& type) : m_type(type) {}
    bool operator()(const data* ptr) const {
        return ptr && ptr->dataS == m_type;
    }
    std::string m_type;
};

long  double instructiontoarithmetic(std::vector<data*> &datas, const instructions* instruction);

#endif