#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char code;
    char cop1;
}command;

int main(){
    unsigned char regs[16];
    char prog_mem[256];
    FILE *fp=fopen("file_read.bin", "rb");
    FILE *fd=fopen("file_data.txt", "w+");
    command *arg;
    arg = (command*)prog_mem;
    if(fp == NULL){
        printf("failed to open bin file\n");
        exit(1);
    }
    if(fd == NULL){
        printf("failed to open txt file\n");
        exit(1);
    }

    for(int i=0; i<sizeof(prog_mem); i++){
        fread(prog_mem+i, 1,1,fp);
        if(feof(fp))
           break;
    }
    
        

    //for(int i = 0; i<20; i++)
    //printf("%u ", prog_mem[i]);
    fclose(fp); 
}