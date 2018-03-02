#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "token.h"

class LexicalAnalyzer
{
    enum Attributes {
        Whitespace = 0,
        Constant = 1,
        Identifier = 2,
        Separator = 3,
        Multichar = 4,
        Comment = 5,
        Invalid = 6
    };
    enum TabRanges {
        keywordsBegin = 300,
        identifiersBegin = 1000,
        constantsBegin = 5000
    };
    struct Symbol {
        char value;
        Attributes attr;
    };

    int m_Attributes[128] = {
        6/*NUL*/, 6/*SOH*/, 6/*STX*/, 6/*ETX*/, 6/*EOT*/, 6/*ENQ*/, 6/*ACK*/, 6/*BEL*/, 0/*BS*/, 0/*TAB*/,
        0/*LF*/, 0/*VT*/, 0/*FF*/, 0/*CR*/, 0/*SO*/, 0/*SI*/, 0/*DLE*/, 0/*DC1*/, 0/*DC2*/, 0/*DC3*/,
        0/*DC4*/, 0/*NAK*/, 0/*SYN*/, 0/*ETB*/, 0/*CAN*/, 0/*EM*/, 0/*SUB*/, 0/*ESC*/, 0/*FS*/, 0/*GS*/,
        0/*RS*/, 0/*US*/, 0/*Space*/, 0/*!*/, 0/*"*/, 0/*#*/, 0/*$*/, 0/*%*/, 0/*&*/, 0/*'*/,
        5/*(*/, 3/*)*/, 3/***/, 3/*+*/, 3/*,*/, 3/*-*/, 3/*.*/, 3/*/*/, 1/*0*/, 1/*1*/,
        1/*2*/, 1/*3*/, 1/*4*/, 1/*5*/, 1/*6*/, 1/*7*/, 1/*8*/, 1/*9*/, 3/*:*/, 3/*;*/,
        4/*<*/, 4/*=*/, 4/*>*/, 4/*?*/, 4/*@*/, 2/*A*/, 2/*B*/, 2/*C*/, 2/*D*/, 2/*E*/,
        2/*F*/, 2/*G*/, 2/*H*/, 2/*I*/, 2/*J*/, 2/*K*/, 2/*L*/, 2/*M*/, 2/*N*/, 2/*O*/,
        2/*P*/, 2/*Q*/, 2/*R*/, 2/*S*/, 2/*T*/, 2/*U*/ , 2/*V*/, 2/*W*/, 2/*X*/, 2/*Y*/,
        2/*Z*/, 2/*[*/, 2/*\*/, 2/*]*/, 2/*^*/, 2/*_*/, 2/*`*/, 2/*a*/, 2/*b*/, 2/*c*/,
        2/*d*/, 2/*e*/, 2/*f*/, 2/*g*/, 2/*h*/, 2/*i*/, 2/*j*/, 2/*k*/, 2/*l*/, 2/*m*/,
        2/*n*/, 2/*o*/, 2/*p*/, 2/*q*/, 2/*r*/, 2/*s*/, 2/*t*/, 2/*u*/, 2/*v*/, 2/*w*/,
        2/*x*/, 2/*y*/, 2/*z*/, 2/*{*/, 2/*|*/, 2/*}*/, 2/*~*/, 2/*DEL*/
    };

    std::vector<Token*> m_Tokens;

public:
    LexicalAnalyzer();
    std::vector<Token*> analyze(std::ifstream &stream, std::map<std::string,int> *keyword, std::map<std::string,int> *identifier, \
                                std::map<std::string,int> *constant, std::vector<std::string> *error);

private:
    Symbol gets(std::ifstream &stream);
    int search(std::map<std::string,int> *table, std::string &token);
    int append(std::map<std::string,int> *table, int RangeBegin, std::string token);
};

#endif // LEXICALANALYZER_H
