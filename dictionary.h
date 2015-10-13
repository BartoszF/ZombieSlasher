#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

struct Dictio
{
    char* Key;
    char* Value;
    struct Dictio* next;
};
typedef struct Dictio Dictionary;

void AddKey(Dictionary** d, char* key, char* value);
void AddKeyValue(Dictionary** d, char* str);
char* GetValue(Dictionary* d, char* key);
void SetValue(Dictionary* d, char* key, char* value);
Dictionary* LoadDictFrom(Dictionary* d, char* file, char* delim);
void SaveDictTo(Dictionary* d, char* file, char* delim);
void DeleteKey(Dictionary* d, char* key);
void DeleteDict(Dictionary* d);


#endif // DICTIONARY_H_INCLUDED
