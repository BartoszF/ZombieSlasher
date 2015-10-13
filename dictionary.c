#include "dictionary.h"
#include <stdio.h>
#include "config.h"

void AddKey(Dictionary** d, char* key, char* value)
{
    if((*d) == 0 || (*d)->Key == NULL)
    {
        Log("Adding : "); Log(key); Log(" "); Log(value); Log("\n");
        *d = malloc(sizeof(Dictionary));
        (*d)->Key = malloc(strlen(key) * sizeof(char));
        (*d)->Key = key;
        (*d)->Value = malloc(strlen(value) * sizeof(char));
        (*d)->Value = value;
        (*d)->next = NULL;
        Log((*d)->Key); Log((*d)->Value); Log("\n");
    }
    else
    {
        Log((*d)->Key); Log(" "); Log(key); Log(" "); Log(value); Log("\n");
        if((*d)->Key == key)
        {
            //Log("Exists\n");
            (*d)->Key = key;
        }
        else
        {
            Log("Next\n");
            AddKey(&(*d)->next,key,value);
        }
    }
}

void AddKeyValue(Dictionary** d, char* str)
{
    char ** res  = NULL;
    char *  p    = strtok (str, " =\0");
    int n_spaces = 0, i;

    while (p) {
      res = realloc (res, sizeof (char*) * ++n_spaces);

      if (res == NULL)
        exit (-1);

      res[n_spaces-1] = p;

      p = strtok (NULL, " =\0");
    }

    AddKey(&d,res[0],res[1]);

    free(res);
}

char* GetValue(Dictionary* d, char* key)
{
    Log("Actual : "); Log(d->Key); Log(" "); Log(d->Value); Log("\n");
    if(d)
    {
        Log("Actual : "); Log(d->Key); Log(" "); Log(d->Value); Log("\n");
        if(strcmp(d->Key,key) == 0) return d->Value;
        else return GetValue(d->next,key);
    }
    return "Not found";
}

void SetValue(Dictionary* d, char* key, char* value)
{
    if(d != NULL)
    {
        if(d->Key == key) d->Value = value;
        else SetValue(d->next,key, value);
    }
}

Dictionary* LoadDictFrom(Dictionary* d, char* file, char* delim)
{
    Log("\nOpening file : ");
    Log(file);
    Log("\n");

    FILE *f;
    f = fopen(file, "r");

    if(f != NULL)
    {
        Log("File opened...\n");

        char line[1023];
        char str[128];
        char* key;
        char* value;
        char delim;
        char c;
        int i=0;

        Log("Reading...\n");

        while(!feof(f))
        {
            fgets(line,1023,f);
            //Log(line);//Log("\n");
            AddKeyValue(&d,line);
        }

        fclose(f);
    }
    else
    {
        Log("Nie moge otworzyc pliku!\n");
    }

    return d;
}

void SaveDictTo(Dictionary* d, char* file, char* delim)
{
    Log("Opening file : ");
    Log(file);
    Log("\n");

    FILE * f = fopen(file,"wt");

    if(f)
    {
        Log("File opened\n");
        while(d != NULL && d->next != NULL)
        {
            fprintf(f,"%s%s%s \n\0",d->Key,delim,d->Value);
            Log("Saving : ");
            Log(d->Key);
            Log(delim);
            Log(d->Value);
            Log("\n");
            fflush(f);
            d = d->next;
        }

        if(d->next == NULL)
        {
            fprintf(f,"%s%s%s \0",d->Key,delim,d->Value);
            Log("Saving : ");
            Log(d->Key);
            Log(delim);
            Log(d->Value);
            Log("\n");
            fflush(f);
        }

        fprintf(f,"\0");
        fclose(f);

        Log("\n");
    }
}

void DeleteKey(Dictionary* d, char* key)
{
    if(d->Key == key)
    {
        Dictionary* temp = d;
        d = d->next;

        free(temp);
        temp = NULL;
    }
    else
    {
        Dictionary* temp = d->next;
        //while(temp->next != NULL && )

    }
}

void DeleteDict(Dictionary* d)
{
    free(d);
    d = NULL;
}
