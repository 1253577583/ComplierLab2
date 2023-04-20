#include "node.h"

pNode tokenNode(int lineNo, NodeType type, char* tokenName,
                                 char* tokenText) {
    pNode tokenNode = (pNode)malloc(sizeof(Node));
    tokenNode->lineNo = lineNo;
    tokenNode->type = type;

    tokenNode->name = (char*)malloc(sizeof(char) * (strlen(tokenName) + 1));
    tokenNode->val = (char*)malloc(sizeof(char) * (strlen(tokenText) + 1));

    strncpy(tokenNode->name, tokenName, strlen(tokenName) + 1);
    strncpy(tokenNode->val, tokenText, strlen(tokenText) + 1);

    tokenNode->child = NULL;
    tokenNode->next = NULL;

    return tokenNode;
}

pNode syntaxNode(int lineNo, NodeType type, char* syntaxName, int argc,
                            ...) {
    pNode fatherNode = (pNode)malloc(sizeof(Node));
    fatherNode->lineNo = lineNo;
    fatherNode->type = type;

    fatherNode->name = (char*)malloc(sizeof(char) * (strlen(syntaxName) + 1)); 
    strncpy(fatherNode->name, syntaxName, strlen(syntaxName) + 1);

    va_list vaList;
    va_start(vaList, argc);
    pNode childNode = va_arg(vaList, pNode);
    fatherNode->child = childNode;
    for (int i = 1; i < argc; i++) {
        childNode->next = va_arg(vaList, pNode);
        if (childNode->next != NULL) {
            childNode = childNode->next;
        }
    }
    va_end(vaList);
    return fatherNode;
}

void printSyntaxTree(pNode curNode, int height) {
    if (curNode == NULL) {return;}

    for (int i = 0; i < height; i++) {
        printf("  ");
    }
    printf("%s", curNode->name);
    if (curNode->type == SYNTAX) {
        printf(" (%d)", curNode->lineNo);
    } else if (curNode->type != OTHER) {
        printf(": %s", curNode->val);
    } 
    printf("\n");
    printSyntaxTree(curNode->child, height + 1);
    printSyntaxTree(curNode->next, height);
    free(curNode);
}

char* newString(char* src) {
    if (src == NULL) return NULL;
    int length = strlen(src) + 1;
    char* p = (char*)malloc(sizeof(char) * length);
    assert(p != NULL);
    strncpy(p, src, length);
    return p;
}