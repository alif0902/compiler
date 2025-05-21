#include"global_0.h"
int main(){
    init();
    int a;

    while((a=lexan()) != DONE){
        printf("tokenval = %4d , token = %4d\n",tokenval, a);
    }
    
    exit(0);
}