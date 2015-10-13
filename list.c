#include "list.h"
#include <stdlib.h>

void AddToList(List** l,List* prev,char* str)
{
    if(*l==NULL)
    {
        (*l) = malloc(sizeof(List));
        (*l)->str = malloc(strlen(str)*sizeof(char));
        strcpy((*l)->str,str);
        //(*l)->str = str;
        (*l)->prev = prev;
        (*l)->next = NULL;
    }
    else
    {
        AddToList(&(*l)->next,(*l),str);
    }
}
