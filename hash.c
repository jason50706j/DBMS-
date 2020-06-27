#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

struct hash {
    int data;
    int key;
    hash *ptr;
};

struct hash *hasharray[SIZE];
struct hash *item;

int hashcode(int key){
  return key%SIZE;
}

struct hash* search (int key){
    int hashindex = hashcode(key);
    while(hasharray[hashindex] != null){
        if(hasharray[hashindex] -> key == key)
            return hasharray[hashindex];
        else{
            hasharray[hashindex] = hasharray[hashindex]->ptr;
        }
        //++hashindex;
        //hashindex%=SIZE;
    }
    return null;
}

void insert(int key ,int data){
    struct hash *item=(struct item*)malloc(sizeof(struct hash));
    struct hash *current=(struct item*)malloc(sizeof (struct hash));
    item->data=data;
    item->key=key;
    int hashindex=hashcode(key);
    hasharray[hashindex]=current
    current->ptr=null;
    while(hasharray[hashindex] != null){
        struct hash *next=(struct item*)malloc(sizeof (struct hash));
        if(current->ptr==null){
            next->data=data;
            next->key=key;
            current->ptr=next;
            current->ptr=null;
        }
        //++hashindex;
        //hashindex%=SIZE;
    }
    hasharray[hashindex] = item;
}

void deletehash(struct hash* item){
    int key = item->key;
    int hashindex =hashcode(key);
    struct hash *current=(struct item*)malloc(sizeof (struct hash));
    while(hasharray[hashindex] != null){
        if(hasharray[hashindex]->key==key){
            struct hash* temp= hasharray[hashindex];
            hasharray[hashindex]=hasharray[hashindex]->ptr;
            free(temp);
        }
        else{
            while(hasharray[hashindex]->ptr=current!=null){
                if(current->key==key){
                   struct hash* temp = current;
                   if(current->ptr!=null){
                      current=current->ptr;
                   }
                   free(temp);
                }
            }
        }
        //++hashindex;
        //hashindex%=SIZE;
    }
    return null;
}
int main()
{
    FILE *fptr;
    fptr=fopen("DB_students.csv","w");
    if(fptr==NULL) {}
    else
    {

    }
    return 0;
}
