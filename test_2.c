#include"global_0.h"
extern int lastentry;
int main()
{
    init();
    int a;
    int current_location =1;
    while((a=lexan()) != DONE){
        if(symtable[lastentry].location==NONE)
        {
          symtable[lastentry].location = current_location;
          current_location+=1;
        }
        
        
    }
    printf("****Kigouhyou**** \n ");
    printf("\tIDname | \ttoken | \tlocation \n");
    
    for(int i = 1; i<=lastentry; i++)
        {
          printf("%18s | %8d | %5d  \n",symtable[i].lexptr,symtable[i].token,symtable[i].location);
        }
        return 0;
}