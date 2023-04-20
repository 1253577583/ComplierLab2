#ifndef SEMANTIC_H
#define SEMENTIC_H

#define HASH_TABLE_SIZE 0x3fff
#define STACK_DEEP

#include "node.h"

typedef struct type* pType;
typedef struct fieldList* pFieldList;
typedef struct tableItem* pItem;
typedef struct hashTable* pHash;
typedef struct stack* pStack;
typedef struct table* pTable;

typedef struct type {
    Kind kind;
    union {
        BasicType basic;
        struct {
            pType elem;
            int size;
        } array;
        
        struct {
            char* structName;
            pFieldList field;
        } structure;

        struct {
            int argc;          // argument counter
            pFieldList argv;   // argument vector
            pType returnType;  // returnType
        } function;
    } u;
} Type;

typedef struct fieldList {
    char* name;       // 域的名字
    pType type;       // 域的类型
    pFieldList tail;  // 下一个域
} FieldList;

typedef struct tableItem {
    int symbolDepth;
    pFieldList field;
    pItem nextSymbol;  // same depth next symbol, linked from stack
    pItem nextHash;    // same hash code next symbol, linked from hash table
} TableItem;

typedef struct hashTable {
    pItem* hashArray;
} HashTable;

typedef struct stack {
    pItem* stackArray;
    int curStackDepth;
} Stack;

typedef struct table {
    pHash hash;
    pStack stack;
    int unNamedStructNum;
    // int enterStructLayer;
} Table;

extern pTable table;

pType newType(Kind kind, ...);
pType copyType(pType src);
void deleteType(pType type);
boolean checkType(pType type1, pType type2);
void printType(pType type);

pFieldList newFieldList(char* newName, pType newType);
pFieldList copyFieldList(pFieldList src);
void deleteFieldList(pFieldList fieldList);
void setFieldListName(pFieldList p, char* newName);
void printFieldList(pFieldList fieldList);

pItem newItem(int symbolDepth, pFieldList pfield);
void deleteItem(pItem item);
boolean isStructDef(pItem src);

pHash newHash();
void deleteHash(pHash hash);
pItem getHashHead(pHash hash, int index);
void setHashHead(pHash hash, int index, pItem newVal);

pStack newStack();
void deleteStack(pStack stack);
void addStackDepth(pStack stack);
void minusStackDepth(pStack stack);
pItem getCurDepthStackHead(pStack stack);
void setCurDepthStackHead(pStack stack, pItem newVal);

pTable initTable();
void deleteTable(pTable table);
pItem searchTableItem(pTable table, char* name);
boolean checkTableItemConflict(pTable table, pItem item);
void addTableItem(pTable table, pItem item);
void deleteTableItem(pTable table, pItem item);
void clearCurDepthStackList(pTable table);

unsigned int getHashCode(char* name);

void pError(ErrorType type, int line, char* msg);

void traverseTree(pNode node);

// Generate symbol table functions
void ExtDef(pNode node);
void ExtDecList(pNode node, pType specifier);
pType Specifier(pNode node);
pType StructSpecifier(pNode node);
pItem VarDec(pNode node, pType specifier);
void FunDec(pNode node, pType returnType);
void VarList(pNode node, pItem func);
pFieldList ParamDec(pNode node);
void CompSt(pNode node, pType returnType);
void StmtList(pNode node, pType returnType);
void Stmt(pNode node, pType returnType);
void DefList(pNode node, pItem structInfo);
void Def(pNode node, pItem structInfo);
void DecList(pNode node, pType specifier, pItem structInfo);
void Dec(pNode node, pType specifier, pItem structInfo);
pType Exp(pNode node);
void Args(pNode node, pItem funcInfo);

#endif

