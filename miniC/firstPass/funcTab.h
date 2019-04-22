#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <stdio.h>
// #include <algorithm>
#include <utility>
#include <fstream>
using namespace std;

enum eletype {INTEGER, FLOATING, NULLVOID, BOOLEAN, ERRORTYPE};
enum varType {SIMPLE, ARRAY};
enum Tag{PARAMAETER, VARIABLE};

struct expression{
    eletype type;
    string* registerName;
    string* offsetRegName;
};

struct stmt {
    vector<int> *nextList;
    vector<int> *breakList;
    vector<int> *continueList;
};

struct whileexp {
    int begin;
    vector<int> *falseList;
};

struct shortcircuit{
    eletype type;
    string* registerName;
    vector<int>* jumpList;
};

struct condition2temp{
    vector<int> *temp;
};

struct switchcaser{
    vector<int> *nextList;
    vector<pair<string,int>> *casepair;
    vector<int> *breakList;
    vector<int> *continueList;
};

struct switchtemp{
    vector<pair<string,int>> *casepair;
};

struct typeRecord {
    string name;
    varType type;
    eletype eleType;
    Tag tag;
    int scope;
    vector<int> dimlist; // cube[x][y][z] => (x -> y -> z)
    int varOffset;
    bool isValid;
    int maxDimlistOffset;
}; 

struct funcEntry {
    string name;
    eletype returnType;
    int numOfParam;
    int functionOffset;
    vector <typeRecord*> variableList;
    vector <typeRecord*> parameterList;
}; 

void patchDataType(eletype type, vector<typeRecord*> &typeRecordList, int scope);
void insertSymTab(vector<typeRecord*> &typeRecordList, funcEntry* activeFuncPtr);
void insertParamTab(vector<typeRecord*> &typeRecordList, funcEntry* activeFuncPtr);
void deleteVarList(funcEntry* activeFuncPtr, int scope);
void searchFunc(funcEntry* activeFuncPtr,vector<funcEntry*> &funcEntryRecord,int &found);
void compareFunc(funcEntry* &activeFuncPtr,vector<funcEntry*> &funcEntryRecord,int &found);
void searchVariable(string name, funcEntry* activeFuncPtr, int &found, typeRecord *&vn, int scope);
void searchCallVariable(string name, funcEntry* activeFuncPtr, int &found, typeRecord *&vn);
void searchParam(string name, vector<typeRecord*> &parameterList, int &found, typeRecord *&pn);
void addFunction(funcEntry* activeFuncPtr, vector<funcEntry*> &funcEntryRecord);
void printList(vector<funcEntry*> &funcEntryRecord);
void printFunction(funcEntry* &activeFuncPtr);
bool arithmeticCompatible(eletype type1, eletype type2);
eletype compareTypes(eletype type1, eletype type2);

void populateOffsets(vector<funcEntry*> &funcEntryRecord);
void printSymbolTable(vector<funcEntry*> &funcEntryRecord);
string eletypeMapper(eletype a);
int eletypeIntMapper(eletype a);
int varTypeMapper(varType a);
int TagMapper(Tag a);