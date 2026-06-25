#include <stdio.h>
#include <string.h>

#define MAX_KEY_LEN 32
#define MAP_SIZE 1024

typedef struct {
    char key[MAX_KEY_LEN];
    int offset;
    int is_occupied;
} HashEntry;


void db_add(char* db, HashEntry* hm, char *key, char* value);
void db_read(char *key, char* db, HashEntry *hm);
//void db_restart(char *db, HashEntry *hm) muss die db von hinten lesen um hashmap wieder herzustellen

int main(void)
{
    HashEntry hash_map[MAP_SIZE] = {0};
    char db[42000] = {"\0"};

    db_add(db, hash_map, "32", "hello");
    db_add(db, hash_map, "43", "bye");

    printf("this is the db: %s\n", db);
    db_read("43", db, hash_map);
    printf("safe\n");
    db_read("32", db, hash_map);
    
}

void db_add(char* db, HashEntry* hm, char *key, char* value)
{
    int i = 0;
    while (hm[i].is_occupied == 1)
        i++;
    int k = hm[i].offset;
    if (i > 0)
        k = hm[i - 1].offset;
    int j = 0;
    while (key[j])
    {
        db[hm[i].offset + k] = key[j];
        hm->key[k] = key[j];
        k++;
        j++;
    }
    j = 0;
    while (value[j])
    {
        db[hm[i].offset + k] = value[j];
        j++;
        k++;
    }
    hm[i].is_occupied = 1;
    hm[i + 1].offset = k;
}

void db_read(char *key, char* db, HashEntry *hm)
{
    int i = 0;
    while (strncmp(key, hm[i].key, strlen(key)) != 0)
    {
        i++;
    }
    printf("%i\n", i);
    printf("%c\n", db[hm[i].offset]);
    int start = hm[i].offset + strlen(key);
    printf("%i\n", start);
    int len = hm[i+1].offset - start;
    int j = 0;
    while (j < len)
    {
        printf("%c", db[start + j]);
        j++;
    }
    printf("\n");
}