#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


typedef struct listt
{
    char* str;
    struct listt* prev;
    struct listt* next;
}List;

void AddToList(List** l,List* prev, char* str);



#endif // LIST_H_INCLUDED
