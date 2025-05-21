#include"global_0.h"

int main(){
    init();
    int a;
    int cnt = 1;
    while((a=lexan()) != DONE){
        printf("tokenval = %4d , token = %4d\n",tokenval, a);
        
    }
    printf("****Kigouhyou**** \n ");
    printf("\tIDname | \ttoken | \tlocation \n");
        
    while(symtable[cnt].lexptr != NULL)
        {
          printf("%18s | %8d | %5d  \n",symtable[cnt].lexptr,symtable[cnt].token,symtable[cnt].location);
          cnt++;
        }
        return 0;
}