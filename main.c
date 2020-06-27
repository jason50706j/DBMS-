#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define READ_FILE  sorted_big5(2).csv
//the type of Tuple
typedef struct tuple{
    char *student_id;
    int course_id;
    char *coures_name;
    int index;
    struct tuple *nextPtr;
}tuple;


int toIntId(char *stringId); //student_id from type string to type int
void init(tuple* currPtr, char* tmp);
//create
tuple* createLinkList(FILE *filePtr, int longtuple);
//insert
tuple *insert(tuple *frist, tuple *data);
tuple *InsertCurrent(tuple *currPtr, tuple *data);
tuple *deleteNode(tuple *first,tuple data);
void createNewFile(char* fileName, tuple* headPtr, char** column);
tuple *buildList (int index);
void findByStuID(char *StuID);
tuple *tuplecpy(tuple *Dest,tuple *Sourse);

int main()
{
    char tmp[200]={0};
    FILE *filePtr;
    char *column[10]; //database columns
    tuple *headPtr = (tuple*)malloc(sizeof(tuple));
    if((filePtr = fopen("sorted_big5(2).csv", "r+")) == NULL){
        printf("File could not be opened\n");
    }
    else{
        //printf("out\n");
        fscanf(filePtr, "%s", tmp);//第一個tuple空值處理
        column[0] = strtok(tmp,",");
        for(int i=1;i<4;i++){
            column[i] = strtok(NULL,",");
        }
        printf("%s %s %s %s\n", column[0], column[1], column[2], column[3]);
        headPtr=createLinkList(filePtr, 1000);
        createNewFile("sorted_test1.csv", headPtr, column);
    }
    fclose(filePtr);
    printf("endof Creating\n\n");
    findByStuID("D000003506");
   
    return 0;
}

int toIntId(char *stringId){
    return atoi(++stringId);
}

void init(tuple* currPtr, char* tmp){
    currPtr->nextPtr=NULL;
    currPtr->student_id = strtok(tmp,",");
    sscanf(strtok(NULL,","), "%d", &currPtr->course_id);//int轉換
    currPtr->coures_name=strtok(NULL,",");
    //printf("%s", strtok(NULL,","));
    currPtr->index=atoi(strtok(strtok(NULL,","),"\n"));
    //printf(" %d\n", atoi(strtok(NULL,",")));
    //currPtr->index=atoi(strtok(NULL,","));
    //printf(" %d\n",currPtr->index);
}

tuple* createLinkList(FILE *filePtr, int longtuple){
    printf("increateLinkList\n");
	char* tmp = (char*)malloc(sizeof(tuple)*40);
    //char tmp[200]={0};
    tuple *headPtr=(tuple*)malloc(sizeof(tuple));
    tuple *currPtr=headPtr;
    int index=1;
    fscanf(filePtr, "%s%*c", tmp);
    /*headPtr->index=index;
    headPtr->student_id = strtok(tmp,",");
    sscanf(strtok(NULL,","), "%d", &headPtr->course_id); //int轉換
    headPtr->coures_name=strtok(NULL,",");*/
    init(headPtr,tmp);
   // printf("id : %d\n",index );
  //  printf("%10s %9d %11s\n", headPtr->student_id, headPtr->course_id, headPtr->coures_name);
    tmp=(char*)malloc(sizeof(char)*50);
    while(fgets(tmp,200,filePtr)){
        tuple *currentData = (tuple*)malloc(sizeof(tuple));
        index++;
        if(index==longtuple)break;
        if((index%10000)==0)printf("already have: %d\n", index);
        init(currentData, tmp);

        currPtr->nextPtr=currentData;
        currPtr=currPtr->nextPtr;
        //printf("%d ",currPtr->index);
        tmp=(char*)malloc(sizeof(char)*50);
        //printf("id : %d\n",index );
        //printf("current: %10s %9d %11s\n", currentData->student_id, currentData->course_id, currentData->coures_name);
        //printf("head: %10s %9d %11s\n", headPtr->student_id, headPtr->course_id, headPtr->coures_name);
        //headPtr = insert( headPtr, currentData);
        //printf("after head: %10s %9d %11s\n", headPtr->student_id, headPtr->course_id, headPtr->coures_name);
        //char* tmp=(char*)malloc(sizeof(char)*50);

    }
    printf("finish create link list\n");
    return headPtr;
}

tuple *insert(tuple *first, tuple *data)
{
    int firstId =0;
    int dataId = toIntId(data->student_id);
    if (first !=NULL){
        //printf("%s\n",first->student_id);
        firstId = toIntId(first->student_id);
        //printf("%d %d\n",dataId, firstId);
    }
    tuple *currPtr = first;

    if(first == NULL){
        printf("Eorr\n");
    }
    else if( (dataId<firstId) || (dataId==firstId&&data->course_id<first->course_id) ){
        //printf("222\n");
        data->nextPtr=first;
        first=data;
    }
    else if(first->nextPtr==NULL){
        //printf("123\n");
        first->nextPtr= data;
    }
    else{
        //以id由小排到大，算出crrent值
        //printf("nok\n");
        currPtr=InsertCurrent(currPtr, data);
        printf("ok\n");
        if(currPtr->nextPtr == NULL){
            currPtr->nextPtr =data;
        }
        else{
            data->nextPtr = currPtr->nextPtr;
            currPtr->nextPtr = data;
        }
    }
    return first;
}

//以id由小排到大，算出insert要插入的地方
//回傳值的nest為要插入的地方
tuple *InsertCurrent(tuple *currPtr, tuple *data){
    if(currPtr==NULL)printf("currPtr is NULL");
    else if(currPtr->nextPtr == NULL)return currPtr;

    int nextNodeId = toIntId( currPtr->nextPtr->student_id );
    int dataId=toIntId(data->student_id);
    while( nextNodeId < dataId){
        //printf("2.111");
        currPtr=currPtr->nextPtr;
        if(currPtr->nextPtr==NULL)break;
        nextNodeId = toIntId( currPtr->nextPtr->student_id );
        dataId=toIntId(data->student_id);
    }
    while( nextNodeId == dataId){
        //printf("2.2222");
        if(currPtr->nextPtr==NULL)break;
        if( currPtr->nextPtr->course_id >= data->course_id)break;
        currPtr=currPtr->nextPtr;
        //printf("2.2222");
        if(currPtr->nextPtr==NULL)break;
        nextNodeId = toIntId( currPtr->nextPtr->student_id );

        dataId=toIntId(data->student_id);
    }
    //printf("endcurrent\n");
    return currPtr;
}

tuple *deleteNode(tuple *first,tuple data){
    tuple *currPtr = first;
    tuple *temp = first;
    int firstId=toIntId(first->student_id);
    int dataId=toIntId(data.student_id);
    int currNextId=toIntId(currPtr->nextPtr->student_id);
    if(first->nextPtr == NULL){
        free(first);
        return NULL;
    }
    else if(currPtr->nextPtr->nextPtr == NULL){
        free(currPtr->nextPtr);
        currPtr->nextPtr = NULL;
    }
    else if(firstId == dataId){

        first = first->nextPtr;
        free(temp);
    }
    else if(currNextId == dataId){
        temp = currPtr->nextPtr;
        currPtr->nextPtr = currPtr->nextPtr->nextPtr;
        free(temp);

    }
    return first;
}

void createNewFile( char* fileName, tuple* headPtr, char **column ){
    tuple* currPtr=headPtr;  
    FILE *fPtr;
    printf("%s\n", fileName);
    if((fPtr=fopen(fileName, "w"))==NULL){
        printf("result file could not be opened\n");
    }
    else{
        printf("writing\n");
        for(int i=0;i<4;i++){
            fprintf(fPtr, "%s", column[i]);
            if(i!=3)fprintf(fPtr, ",");
        }
        fprintf(fPtr, "\n");
        printf("column is already ok\n");
        while(currPtr!=NULL){
            fprintf(fPtr, "%s,", currPtr->student_id);
            fprintf(fPtr, "%d,", currPtr->course_id);
            fprintf(fPtr, "%s,", currPtr->coures_name);
            fprintf(fPtr, "%d\n", currPtr->index);
            currPtr=currPtr->nextPtr;
        }

    }
}
void findByStuID(char *StuID)
{
	int index = 0;
	FILE *fp = fopen("re.txt","w+");
	tuple* Data = buildList(index);
	tuple* currentPtr = Data;
	//char *curr = (char*)malloc(sizeof(Data.student_id));
	int flag = 0;
	while(flag == 0)
	{	
		Data = buildList(index);
		printf(">>* %s\n",Data->course_id);
		while(currentPtr->nextPtr != NULL)//search
		{
			if(strcmp(Data->student_id,StuID) == 0)
			{
				flag = 1;
				fprintf(fp,"%s %d %s\n",Data->course_id,Data->course_id,Data->coures_name);
			}
			if(flag == 1 && strcmp(Data->student_id,StuID) != 0)
			{
				break;
			}
			currentPtr = currentPtr->nextPtr;
		}
		index++;
		
	}
	fclose(fp);
}

tuple *buildList (int index)
{
	printf("inBuildList\n");
	
	FILE *fp = fopen("sorted_big5(2).csv", "r+");
	tuple *head = createLinkList(fp, 100);
	printf(">> %s\n",head->nextPtr->student_id);

	return head;
}  
tuple *tuplecpy(tuple *Dest,tuple *Sourse)
{
	Dest->coures_name = Sourse->coures_name;
	Dest->course_id = Sourse->course_id;
	Dest->student_id =  Sourse->student_id;
	Dest->index =  Sourse->index;
	Dest->nextPtr = Sourse->nextPtr;
	return Dest;
}

