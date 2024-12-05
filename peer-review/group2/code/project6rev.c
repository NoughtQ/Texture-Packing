#include<stdio.h>
#include<stdlib.h>
#include<time.h>  //to calculate time


typedef struct
{
    int width;
    int height;
} item;  //define the structure of item
typedef item*  Item;  


void downheap(Item* a, int i, int P)//its a maxheap implementation, maximum height
{
    while(2*i+1 <= P)//if the left child exist
    {
        int j = 2*i;
        if(j < P && a[j]->height < a[j+1]->height)//if the right child exist and the right child is larger than the left child
            j++;
        if(a[i]->height >= a[j]->height) //if the parent is larger than the child
           break;
        Item temp = a[i];//swap the parent
        a[i] = a[j];
        a[j] = temp;
        i = j;
    }
}  
void sortheap(Item* a, int P)//heap sort
{
    for (int i = P; i >= 1; i--) 
       downheap(a, i, P);
}  
void upheap(Item* a, int i)//upheap procedure
{
    while(i > 1 && a[i/2]->height < a[i]->height)//if the parent is smaller than the child
    {
        Item temp = a[i];//swap the parent
        a[i] = a[i/2];
        a[i/2] = temp;
        i = i/2;
    }
}
void insert(Item* a, Item x, int P)//insert a new item
{
    a[P + 1] = x;//insert the new item
    P++;
    upheap(a, P);//upheap the new item
}   
void pop(Item* a, int P)//delete the top item
{
    if(P==0)//if the heap is empty
    {
        return;
    }
    a[1] = a[P];//swap the top item with the last item
    P--;
    downheap(a, 1, P);//downheap the top item
}  
void deleteitem(Item* a, int i, int P)//delete the item at the ith position
{
    a[i] = a[P];
    P--;//swap the ith item with the last item
    downheap(a, i, P);
}
void delete1(Item* a, int i, int P)
{
    for(int j=i;j<P;j++)
    {
        a[j]=a[j+1];
    }   
    P--;
}
void insertitem(Item* a, int P)
{
    for(int i=P;i>1;i--)
    {
        if(a[i]->height>a[i+1]->height)
        {
            Item temp=a[i];
            a[i]=a[i+1];
            a[i+1]=temp;
        }
        else 
        {
            break;
        }
    }
}
 

int main()//main function  
{
    double start, end, result; //variables for time measurement 

    int N, B, W;//introduce variables for input  
    FILE* input;//file pointer
    input=fopen("test_cases/test.txt", "r");//open the input file
    fscanf(input,"%d %d", &N, &W);    
    Item* item1 = (Item*)malloc((N+1)*sizeof(Item)); //allocate memory for the item array  
    for(int i=0;i<=N;i++)//allocate memory for each item
    {
        item1[i]=(Item)malloc(sizeof(item));
    }  
    for (int i = 1; i <= N; i++) //read the width and height of each item
        fscanf(input,"%d %d", &item1[i]->width, &item1[i]->height);  
    start=clock();//the start of time
    sortheap(item1, N);  //heap sort
    Item* block = (Item*)malloc((2*N+1)*sizeof(Item));  //allocate memory for the block array        
    for(int i=0;i<=N;i++)//allocate memory for each block
    {
        block[i]=(Item)malloc(sizeof(item));
    }  
    block[1]->width=W-item1[1]->width;//initialize the first block  
    block[1]->height=item1[1]->height;  
    int H=item1[1]->height;  
    int i;
    pop(item1, N);//delete the first item  
    N=N-1;
    int count=0;     
    int amountBlock=1;//initialize the amount of block
    int assist1,assist2;
    
    while(N>0)//when there are still items that aren't placed $O(N)~O(N^3)$
    {
    for(i=1;i<=amountBlock;i++)//when there are still blocks that haven't been chosen
    {
        if(block[i]->width>=item1[1]->width&&block[i]->height>=item1[1]->height)//if the item can be placed in this block
        {
            assist1=block[i]->height;//store the height of the block
            assist2=block[i]->width;//store the width of the block
            delete1(block, i ,amountBlock); //delete the item
            amountBlock--;
            block[amountBlock+1]->width=assist2-item1[1]->width;//update the width of the block
            block[amountBlock+1]->height=item1[1]->height; 
            
            insertitem(block, amountBlock);   
            amountBlock++; //insert the new block
            block[amountBlock+1]->width=item1[1]->width;  //create a new block
            block[amountBlock+1]->height=assist1-item1[1]->height;  //update the height of the block
            insertitem(block, amountBlock);  
            amountBlock++;  //insert the new block
       
            count++;
            break;
        }
    }   
    if(i>amountBlock)//if the item cannot be placed in any block
    {
        block[amountBlock+1]->width=W-item1[1]->width;//create a new block
        block[amountBlock+1]->height=item1[1]->height;
        H=H+block[amountBlock+1]->height;  //update the height of the block
        insertitem(block,amountBlock);  
        amountBlock++;
        count++;
    }
    pop(item1, N);//delete the item
    N=N-1;
    }  
    end=clock();
    result=(end-start)*1000000/CLOCKS_PER_SEC;//calculate the time,and the unit is us
    printf("%d %lfus\n", H, result);
     

    free(item1);  //free the memory

    free(block);//free the memory
    free(input);//free the file

    return 0;
}