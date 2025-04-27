#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
#define SIZEWORD 50
#include <string.h>
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Teacher : Radi jarar
Student's Name: Ahmad Shaher Ahmad Sous
Student's Number:1221371

Aim of the Project:-

The project aims:- to develop a text editor using an undo/redo stack.


Main Design of the Data Structure:-

The project will store the initial text from a file and perform insertion and deletion operations on it(on characters and strings).
and we do undo to back to previous operation and redo to do next operation then we store it in file.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
struct nodeQueue{                                     //node to create malloc for Queue to store data
struct nodeQueue* next;                               //pointer to point next node
char word[50];                                        // to store word

};
typedef struct nodeQueue* Queue;

struct Queue{                                          //node to create front and rear
struct nodeQueue *front,*rear;                         //pointer front and rear to point to Queue's nodes
};
typedef struct Queue* queue;


struct nodestack{                                      //node to create undoStack and redoStack
struct nodestack* next;                                //pointer to point next node
char word[50];                                         // to store word
char operation[10];                                    // to store opertion
int index;                                             //to store position for first index for word in text and if word insert in last stoe -1
int index2;                                            //to store position for first index for word in text
};
typedef struct nodestack* stack;

char * loadinInformation(stack undoStack,stack redoStack);                           //to loading text from file to text
void printLoadingInformation(char s[]);               //to print loading text from file
void insert (char s[],stack Stack, queue Q,stack redoStack);          //to insert new character or string from user to text
void dequeue(queue Q);                                //to delete first node from Queue
void enqueue(queue Q,char x[]);                       //to insert new node (new word) in last Queue
queue createQueue();                                  //to create Queue
stack createStack();                                  //to create stack to create undo/redo stack
void push(stack top,char word[],char operation[],int index,int index2);      //to insert node with data in first stack
void Remove(stack Stack,char text[],stack redoStack);                                        //to delete first character or string from user to text
void performUndOperation(stack topUndoStack,stack topRedoStack,char text[]); //to do undo to back to previous operation delete last opertaion
void insertInText(char text[],char word[],int index);                        //to insert string to text but in undo/redo stack
void removeInText(char text[],char word[],int index);                        //to delete string to text but in undo/redo stack
void performRedoOperation(stack topUndoStack,stack topRedoStack,char text[]);//to do redo to back to previous operation delete last opertaion
void printUndoAndRedoStack(stack q1,stack q2);                               //to print undo and redo stack
void printOutput (char text[]);                                              //to save out put text in file
void deleteALL(stack undoStack,stack redoStack,queue Q);                     //to delete all nodes from memory
void makeEmptyRedoSack(stack redoStack);                                             //to make empty redoStack;


int main()
{
char *text= (char *)malloc(sizeof(char)*SIZE);                               //to create array of character(string) with size
char *text1= (char *)malloc(sizeof(char)*SIZE);                               //to create array of character(string) with size
stack undoStack=createStack();                                               //to create undoStack
stack redoStack=createStack();                                               //to create redoStack
text1=loadinInformation(undoStack,redoStack);
queue Q=createQueue();                                                       //to create Queue
int selection=0;                                                             //variable to store selection
do{
printf("please enter number between 1-10: ");
printf("\n\n1. Load the input file which contains the initial text.");
printf("\n2. Print the loaded text.");
printf("\n3. Insert strings to the text.");
printf("\n4. Remove strings from the text.");
printf("\n5. Perform Undo operation");
printf("\n6. Perform Redo operation");
printf("\n7. Print the Undo Stack and the Redo stack");
printf("\n8. Save the updated text to the output file.");
printf("\n9. print the current text.");
printf("\n10. Exit\n\n");
printf("The selection is:- ");
scanf("%d", &selection);
printf("\n");
if(selection == 1) text = loadinInformation(undoStack,redoStack);
else if(selection == 2) printLoadingInformation(text1);
else if(selection ==3)  insert (text,undoStack,Q,redoStack);
else if(selection == 4) Remove(undoStack,text,redoStack);
else if(selection == 5) performUndOperation(undoStack,redoStack,text);
else if(selection == 6) performRedoOperation(undoStack,redoStack,text);
else if(selection == 7) printUndoAndRedoStack(undoStack,redoStack);
else if(selection == 8) printOutput(text);
else if(selection == 9) printf("The current text is:-\"%s", text);
else if (selection== 10){
    printf("\t!Thank you!");
    deleteALL(undoStack,redoStack,Q);

}
printf("\n\n");
 }while(selection != 10);

    return 0;
}


char *loadinInformation(stack undoStack,stack redoStack){//TO loading information in string and return it
    FILE *in;
    in = fopen("input.txt","r");
    char *line;
    line = (char *)malloc(sizeof(char)*SIZE); //to create string
    fgets(line,SIZE,in);
    if (line == NULL) printf("No data in file"); //if file NULL
    fclose(in);
   makeEmptyRedoSack(redoStack);
   makeEmptyRedoSack(undoStack);
return line;
}

void printLoadingInformation(char s[]){//to print initail text in file
printf("The initial test is \"%s",s);
}



void insert (char s[],stack Stack,queue Q,stack redoStack){         //to insert new character or string from user to text
    makeEmptyRedoSack(redoStack);
    int flag =0;                                        //to Know if word found or not
    int index1=0;                                       //to Know The index of first character from word that we want add
    int i;
    char a[SIZE];                                        //to store string that we insert after it
    int index2=0;                                        //to Know The index of first character from word and if last is- 1
    getchar();

    printf("\nplease enter where do you want adding the string (after what) if not found insert in last:- ");
    gets(a);
if(a!=NULL){                                         //to select first index for word that we want insert, we check where found then add to index 1
    for(i=0;i<strlen(s);i++){                            //i is the index of character of text ,we increase until it same with first character from new string
        if(s[i]==a[0]){
            index1=i;
            int j=0;
            for(j=0;j<strlen(a);j++){                    //j is the index of character of new string
                if(s[index1]!=a[j]) break;           //after we check first character of new string with first character of text ,we check the other index until long of new string if not same break,and if all same j = new string
                else index1++;
            }
       if(j == (strlen(a))){                        //
            flag = 1;
            break;
       }
    }

}
}
//After we select the position of new string (where the first index from new string is) we insert the new string (we cut string in indix)&& if the word not found insert from last
    index2 =index1;          //index2 is the index that you want push it if in the last is -1
if(flag==0){                 //if word that we want add new string after it is not found
    index1=strlen(s);        //index = long of text until we add new string in last
    }
if(index1==strlen(s)) index2=-1;  //if we add new string in last index2 =-1

    char newString[SIZE];         //the new string that we want add
    printf("please enter the new string that you want:- ");
    fgets(newString, sizeof(newString), stdin); // Read input from stdin
if (newString[strlen(newString) - 1] == '\n') { //don't store the new line like getchar()
    newString[strlen(newString) - 1] = '\0';
    }
    char copyString[SIZE];                     //copy of new string because when we strtok string there are chnge in it
    strcpy(copyString,newString);

    char *word= strtok(copyString," ");        //to cut new srting in each space to divide it to words
while(word!=NULL){
    enqueue(Q,word);                           //to store each word in queue
    word = strtok(NULL," ");
    }

    int initial =0;                           //I use it to insert space if we insert in last in first case
    char x[50];                               //to store the word
    strcpy(copyString,newString);
    char operation[10];
    Queue current =Q->front;                  //first node of queue
    char arr1[SIZE];
    char arr2[SIZE];
    int space =0;
    if(s[index1]==' '){                         //if we want addind after welcome to(after welcome) so there are space the index the we make space =1 and we adding space in last of the string
    space=1;
    if(index2!=-1) {index2++;                  //if index != -1 adding to index2 1 if not staying -1
        index1++;
        }
    }

while(current!=NULL){
    strcpy(x,current->word);
if(current->next!=NULL) strcat(x," ");    //adding space in last of word if not the last word of string
else if(space==1) strcat(x," ");          //adding space in last of word if not the last word of string
    strcpy(operation,"Insert");
if (initial==0&&index2==-1)                //if the word in the last and it is the first word in the string
    push(Stack,x,operation,index2,index1+1); //if we want adding in the last and it is the first word in the string we do space so the index +1
else push(Stack,x,operation,index2,index1);  //if we want adding in the other place the index is the position of the first index of the word

    strncpy(arr1,s,index1);                  //we want to cutting the string from first to the index
    arr1[index1]='\0';                       //the last of first array
    strncpy(arr2, s + index1, strlen(s) - index1);   //cutting from index to the last
    arr2[strlen(s) - index1] = '\0';                 //the last of the second array
if(index2==-1 && initial ==0) strcat(arr1," ");      // if we want adding in the last we add space in the first in (first word in new string)
    strcat(arr1,x);                                  // adding word to the first part
    strcat(arr1,arr2);                               // adding part2 to part1
    current=current->next;                           //to increase to go to the next word in new string
if(index2!=-1) index2+=(strlen(x));                  //to increase index by length of x
    index1+=strlen(x);                               //increase the index by the length of new word to be the index of the next word and if there are space or in the last increase one
if(index2==-1 && initial==0) index1+=1;              // if we want adding in the last (first word in new string) we add one in index because we adding space in the last
    initial++;                                       //to do one just in first
    strcpy(s,arr1);                                  //the new text
    dequeue(Q);                                      //delete the first word and free the first node
 }

}







queue createQueue(){                           //to create queue
queue Q=(struct Queue*) malloc(sizeof(queue)); //to create malloc for front and rear
Q->rear=Q->front=NULL;
if(Q==NULL) printf("out space memory");        //if there are not space in memory
return Q;
}

void enqueue(queue Q,char x[]){                //to insert new word to queue
Queue newNode = (struct nodeQueue*)malloc(sizeof(struct nodeQueue));  //to create new node for word in queue
strcpy(newNode->word,x);
newNode->next=NULL;
if(Q->front==NULL){  //to insert if queue empty
 Q->front=newNode;
 Q->rear=newNode;;
}
else{               //ti insert if queue not empty
    Q->rear->next=newNode;
    Q->rear=newNode;
}

}



void dequeue(queue Q){                     //to  delete first node from queue
 if(Q->front!=NULL){                       //if queue not empty
   Queue temp = (struct nodeQueue*)malloc(sizeof(Queue));
   temp = Q->front;
   Q->front=Q->front->next;
    free(temp);
  }
}



stack createStack(){                        //to create undostack and redostack
struct nodestack* top = (struct nodestack*)malloc(sizeof(stack)); //to create top
top->next=NULL;
if(top==NULL) printf("out space of memory");
return top;
}


void push(stack top,char word[],char operation[] ,int index,int index2){ // to insert in undoStack and redoStack
stack temp = (struct nodestack*)malloc(sizeof(struct nodestack));
temp->index2=index2;
strcpy(temp->operation ,operation);
strcpy(temp->word,word);
temp->index=index;
if(top->next ==NULL){   //if we want insert in first and the stack empty
 top->next= temp;
 temp->next= NULL;
 }
else{                   //if we want insert in first but not empty
 temp->next =top->next;
 top->next=temp;
 }
}


void printUndoAndRedoStack(stack q1,stack q2){   //to print undo and redo stack
stack undoStak =q1->next;  //first node in undostack
stack redoStak =q2->next;  //first node in redoStck
if(undoStak!=NULL) printf("The UndoStak is:\n");    //if stack not empty
else printf("The undoStak empty");
while(undoStak!=NULL){
printf("\n%s | %s | %d",undoStak->word,undoStak->operation,undoStak->index);
    undoStak=undoStak->next;
}
printf("\n\n********************************************************\n\n");
if(redoStak!=NULL) printf("The RedoStak is:\n");  //if redoStack not empty
else printf("The RedoStak empty\n");
while(redoStak!=NULL){
printf("\n%s | %s | %d",redoStak->word,redoStak->operation,redoStak->index);
    redoStak=redoStak->next;
}
}



void Remove(stack Stack,char text[],stack redoStack){  //to remove from text and push operation in undotext
int flag =0;
int index1=0;
int i;
char word[50];
char opertion[10];
printf("\nplease enter the word or the character that you want delete:- "); //insert the word that you want delete
getchar();
gets(word);

if(word!=NULL){          //if word not null
for(i=0;i<strlen(text);i++){  //we want to find the first index for word that we want delete
    if(text[i]==word[0]){
        index1=i;
        int j=0;
        for(j=0;j<strlen(word);j++){
                if(text[index1]!=word[j]) break;
                index1++;
        }
       if(j == (strlen(word))){
        flag = 1;
       break;
       }
    }

}
index1=i;//the first index for word that we want delete

}
else printf("please enter any word and trying the word exist");

if(flag==0)  printf("This word not exist!"); //if the word not exist
else{
strcpy(opertion,"remove");
push(Stack,word,opertion,index1,index1); //to push the operation in undostack


    for ( i = index1; i < strlen(text); i++) { //to remove what you are insert by shifting to the left by the size of word
            text[i] = text[i+strlen(word)];

        }

 }
 makeEmptyRedoSack(redoStack); //to make redoStack empty after any new opertion
}



void pop(stack Stack){    //to remove from undostack and redoStack
    stack copy;
if(Stack->next!=NULL){    //if undo/redo stack not empty
 copy =Stack->next;
 Stack->next=copy->next;
 free(copy);

 }
}


void insertInText(char text[],char word[],int index){  //to insert in text and push in redo and undo stack but from user (from operation in undo and redo stack)
char arr1[SIZE];
char arr2[SIZE];
if(index ==-1) index =strlen(text);                   //if the index -1 the index will be is length of text
strncpy(arr1,text,index);                             //cutting from first to the index without character of index
arr1[index]='\0';                                      //The end of first string(array)
strncpy(arr2, text + index, strlen(text) - index);     //cutting from index and the length of cutting is(length of text - index(The index is the first index of new word))
arr2[strlen(text) - index] = '\0';                     //The end of arr2 (the string that contain the part)
strcat(arr1,word);                                     //adding the first part with word
strcat(arr1,arr2);                                     //adding the first part with second part
strcpy(text,arr1);                                      //putting the new text in the orginal text

}


void removeInText(char text[],char word[],int index){ //to remove in text and push in redo and undo stack but from user (from operation in undo and redo stack)


     for ( int i = index;i < strlen(text)+strlen(word);i++) {
            text[i] = text[i+strlen(word)];
        }



}



void performUndOperation(stack topUndoStack,stack topRedoStack,char text[]){ //to do undo to back to previous operation delete last opertaion
if(topUndoStack->next==NULL){                                                //to check if there are any operation in undo ,if you do any opertion or not
    printf("\nThe undo stack is empty please do operation(remove or Insert)!");
 }
 else {
    if(strcmp(topUndoStack->next->operation,"Insert")==0){                      //if last operation store in redo is insert and then do undo then do remove in text and push in undo
     push(topRedoStack,topUndoStack->next->word,topUndoStack->next->operation,topUndoStack->next->index,topUndoStack->next->index2);    //to push in stack
     removeInText(text,topUndoStack->next->word,topUndoStack->next->index2);                                                        //to remove in text
     pop(topUndoStack);                                                                                                           //pop the last operation in undo
    }
    else{                                                                    //if last operation store in undo is remove and then do undo then do insert in text and push in undo
     push(topRedoStack,topUndoStack->next->word,topUndoStack->next->operation,topUndoStack->next->index,topUndoStack->next->index2); //push in stack
     insertInText(text,topUndoStack->next->word,topUndoStack->next->index);    //insert in text
    pop(topUndoStack);                                        //pop the last operation in undo
    }
 }
}



void performRedoOperation(stack topUndoStack,stack topRedoStack,char text[]){  //to do redo to back to previous operation delete last opertaion
if(topRedoStack->next==NULL){                                                  //to check if there are any operation in redo ,if you do any undo or not
    printf("\nThe Redo stack is empty please do operation(remove or Insert)!");
 }
 else {
    if(strcmp(topRedoStack->next->operation,"Insert")==0){                     //if last operation store in redo is insert and then do redo then do insert in text and push in  undo
     push(topUndoStack,topRedoStack->next->word,topRedoStack->next->operation,topRedoStack->next->index,topRedoStack->next->index2);   //to push in stack
     insertInText(text,topRedoStack->next->word,topRedoStack->next->index2);                                                            //to insert in text

     pop(topRedoStack);                                                                                               //pop the last operation in redo
    }
    else{                                                                     //if last operation store in redo is remove and then do redo then do remove in text and push in undo
     push(topUndoStack,topRedoStack->next->word,topRedoStack->next->operation,topRedoStack->next->index,topRedoStack->next->index2);    //to push in stack
     removeInText(text,topRedoStack->next->word,topRedoStack->next->index2);                                                            //to remove in text
     pop(topRedoStack);                                                                                                                 //pop the last operation in redo
    }
 }
}
void printOutput (char text[]) {   //to print text in output
    // check if there are text or not
    if (text == NULL) {
        printf("text does not exist!\n");
        return;
    }
    FILE *output = fopen("output.txt", "w");
    fprintf(output,"%s",text);               //to print text in file
    fclose(output);
    printf("saving output in file");
    printf("\n\n");
}



void deleteALL(stack undoStack,stack redoStack,queue Q){  //to delete all nodes from memory
    while(undoStack->next!=NULL){                         //to delete all nodes in undostack
            pop(undoStack);
    }
    free(undoStack);                                       //to delete top in undostack

    while(redoStack->next!=NULL){                          //to delete all nodes in redostack
          pop(redoStack);
    }
    free(redoStack);                                       //to delete top in redostack

    free(Q);                                                //to delete front and rear in Queue
}


void makeEmptyRedoSack(stack redoStack){ // to make redo Stack empty
while(redoStack->next!=NULL){
  pop(redoStack);
  }
}
