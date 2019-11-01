#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef struct{
    char code;
    char cop1;
}command;

int running=true;
int ieof_flag=0;

void decode(command*arg_pc, char *duom,long duom_size);
command *fetch1(command *arg_pc);
command *fetch2(command *arg_pc);

int main(){
    char prog_mem[256];
    command *arg_pc;
    char *duom;
    long duom_size;
    arg_pc = (command*)prog_mem;
    FILE *fp=fopen("file_read.bin", "rb");
    FILE *fd=fopen("file_data.txt", "r");
    if(fp == NULL){
        printf("failed to open bin file\n");
        exit(1);
    }
    if(fd == NULL){
        printf("failed to open txt file\n");
        exit(1);
    }
    fseek(fd,0,SEEK_END);
    duom_size=ftell(fd);
    rewind(fd);
    duom = (char*) malloc(sizeof(char)*duom_size);
    fread(duom, 1, duom_size,fd);
    fclose(fd);
    for(int i=0; i<sizeof(prog_mem); i++){
        fread(prog_mem+i, 1,1,fp);
        if(feof(fp))
           break;
    }
    fclose(fp);


    while(running){
        //printf("%x\n", arg_pc->code); 
        if(arg_pc->code == 0x07){
            arg_pc=fetch2(arg_pc);
            decode(arg_pc, duom,duom_size);
        }
        else if(arg_pc->code == 0x0A && ieof_flag==1){
            arg_pc=fetch2(arg_pc);
            decode(arg_pc, duom,duom_size);
        }
        else{
            decode(arg_pc, duom,duom_size);
            arg_pc=fetch1(arg_pc);
        }};   
}

command *fetch1(command *arg_pc){
    return ++arg_pc;
}

command *fetch2(command *arg_pc){   
    arg_pc = (command*)((char*)arg_pc+arg_pc->cop1);        
    return arg_pc;
}

void decode(command*arg_pc,char *duom, long duom_size){
    unsigned char regs[16];
    int tmp_reg1 = arg_pc-> cop1 & 0x0f;
    int tmp_reg2 = arg_pc->cop1 & 0x0f>>4;  
    int comm_code = arg_pc->code, duom_counter=0;
    switch(comm_code){
        case 0x01:
            printf("INC\n");
            break;
        case 0x02:
            printf("DEC\n");
            break;
        case 0x03:
            printf("MOV\n");
            break;
        case 0x04:
            printf("MOVC\n");
            break;
        case 0x05:
            printf("LSL\n");
            break;
        case 0x06:
            printf("LSR\n");
            break;
        case 0x07:
            //printf("JMP ");
            break;
        case 0x0A:
            //printf("JFE ");    
            break;   
        case 0x0B:
            //printf("RET ");
            running = false;
            break;  
        case 0x0C:
            printf("ADD\n");
            break;  
        case 0x0D:
            printf("SUB\n");
            break;
        case 0x0E:
            printf("XOR\n");
            break;
        case 0x0F:
            printf("OR\n");
            break;
        case 0x10:
            //printf("IN ");
            duom_counter++;
            if(duom_counter == duom_size)
                ieof_flag = 1;
            else{
                printf("%d %d\n",duom_counter,duom[duom_counter]);    
                regs[tmp_reg1]=duom[duom_counter];   
                duom_counter++;
            }
            break;  
        case 0x11:
            //printf("OUT ");
              //printf("%c ", regs[tmp_reg1]);
            break;
                   
    }
}
