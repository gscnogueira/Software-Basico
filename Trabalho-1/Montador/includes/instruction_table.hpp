#pragma once

#include <map>
#include <string>

const std::map<std::string, unsigned int8_t> INSTRUCTION_TABLE= {
    {"ADD"    , 1},
    {"SUB"    , 2},
    {"MUL"    , 3},
    {"DIV"    , 4},
    {"JMP"    , 5},
    {"JMPN"   , 6},
    {"JMPP"   , 7},
    {"JMPZ"   , 8},
    {"COPY"   , 9},
    {"LOAD"   , 10},
    {"STORE"  , 11},
    {"INPUT"  , 12},
    {"OUTPUT" , 13},
    {"STOP"   , 14},
};

const std::set<std::string> DIRECTIVES_TABLE= {
    "SPACE",
    "CONST",
    "EXTERN",
    "PUBLIC",
    "SECTION"
};
