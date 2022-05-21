#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    char *markName;
    int addressCounter;
}markSymbol;

typedef struct {
    int len;
    char *item[5];
}instructionEntry;

//标记符号容器
markSymbol **markSymbolContainer=NULL;
//指令容器
instructionEntry **instructionContainer=NULL;

//标记符号容器长度
int markSymbolContainerLen = 0;
//指令容器长度
int instructionContainerLen = 0;

// 指令符号集，有11种合法指令符号
char* symbol[11] = {"lw","sw","add","addi","sub","and","andi","beqz","j","halt","noop"};
// 寄存器名称集，共有32个寄存器
char* registerName[32] = {"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","r16","r17","r18","r19","r20","r21","r22","r23","r24","r25","r26","r27","r28","r29","r30","r31"};

//查找字符串a是否在字符串数组list里面
bool lookup(char* a,  char* list[], int len){
    for(int i=0; i<len; i++){
        if(!strcmp(a,list[i])) return true;
    }
    return false;
}

//检查指令的合法性
bool legal_check(char* instr[], int len){
    //printf("legal_check");

    //如果指令名称不在指令符号集里，则报错
    if(!lookup(instr[0],symbol,11)) return false;

    //I型指令合法性检查
    if(!strcmp(instr[0],"lw")){//lw
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令立即数的范围不是-32768到32767
        int i = atoi(instr[3]);
        if(i<-32768||i>32767) return false;
    }else if(!strcmp(instr[0],"sw")){//sw
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令立即数的范围不是-32768到32767
        int i = atoi(instr[3]);
        if(i<-32768||i>32767) return false;
    }else if(!strcmp(instr[0],"addi")){//addi
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令立即数的范围不是-32768到32767
        int i = atoi(instr[3]);
        if(i<-32768||i>32767) return false;
    }else if(!strcmp(instr[0],"andi")){//andi
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令立即数的范围不是-32768到32767
        int i = atoi(instr[3]);
        if(i<-32768||i>32767) return false;
    }

    //R型指令合法性检查
    else if(!strcmp(instr[0],"add")){//and
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令第三个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[3],registerName,32)) return false;
    }else if(!strcmp(instr[0],"sub")){//sub
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令第三个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[3],registerName,32)) return false;
    }else if(!strcmp(instr[0],"and")){//and
        //指令符号数不是4，则报错
        if(len!=4) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        //指令第二个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[2],registerName,32)) return false;
        //指令第三个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[3],registerName,32)) return false;
    }
    //分支指令
    else if(!strcmp(instr[0],"beqz")){//beqz
        //指令符号数不是3，则报错
        if(len!=3) return false;
        //指令第一个操作数寄存器不在寄存器名称集里，则报错
        if(!lookup(instr[1],registerName,32)) return false;
        
        bool mark_exist = false;
        for(int i=0;i<markSymbolContainerLen;i++){
            if(!strcmp(instr[2],markSymbolContainer[i]->markName)) mark_exist = true;
        }
        if(!mark_exist){
            //该符号没有在标记符号容器里，却也不是立即数,则报错
            for(int i = 0; i<strlen(instr[1]); i++){
                if(instr[1][i]<'0'||instr[1][i]>'9'){
                    //printf("instr[1] is: %s", instr[1]);
                    return false;
                }
            }
            //指令立即数的范围不是-32768到32767，则报错
            //printf("!mark_exist");
            //printf("instr[1] is: %s", instr[1]);
            int i = atoi(instr[1]);
            //printf("immediate is: %d", i);
            if(i<-32768||i>32767) return false;
        }
    }else if(!strcmp(instr[0],"j")){//j
        //printf("j");
        //指令符号数不是2，则报错
        if(len!=2) return false;

        //检查该符号是否在标记符号容器里
        bool mark_exist = false;
        for(int i=0;i<markSymbolContainerLen;i++){
            if(!strcmp(instr[1],markSymbolContainer[i]->markName)) mark_exist = true;
        }

        if(!mark_exist){
            //该符号没有在标记符号容器里，也不是立即数，则报错
            for(int i = 0; i<strlen(instr[1]); i++){
                if(instr[1][i]<'0'||instr[1][i]>'9'){
                    //printf("instr[1] is: %s", instr[1]);
                    return false;
                }
            }
            //指令立即数的范围不是-32768到32767，则报错
            //printf("!mark_exist");
            //printf("instr[1] is: %s", instr[1]);
            int i = atoi(instr[1]);
            //printf("immediate is: %d", i);
            if(i<-33,554,432||i>33,554,431) return false;
        }
    }else if(!strcmp(instr[0],"halt")){//halt
        //指令符号数不是1，则报错
        if(len!=1) return false;
    }else if(!strcmp(instr[0],"noop")){//noop
        //指令符号数不是1，则报错
        if(len!=1) return false;
    }

    return true;
}


//将一行汇编指令转换成机器码
void turn_assemble_to_machinecode(char* instr[], char* str, int address){
    if(!strcmp(instr[0],"addi")){//addi
        int opcode = 8;
        //rs
        char* _rs = instr[2];
        strcpy(_rs,_rs+1);
        int rs = atoi(_rs);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        //immediate
        int immediate = atoi(instr[3]);
        int total = (opcode<<26) | (rs<<21) | (rd<<16) | (immediate&0xFFFF);
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"lw")){//lw
        int opcode = 35;
        //rs
        char* _rs = instr[2];
        strcpy(_rs,_rs+1);
        int rs = atoi(_rs);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        //immediate
        int immediate = atoi(instr[3]);
        int total = (opcode<<26) | (rs<<21) | (rd<<16) | (immediate&0xFFFF);
        itoa(total,str,10); 
    }else if(!strcmp(instr[0],"sw")){//sw
        int opcode = 43;
        //rs
        char* _rs = instr[2];
        strcpy(_rs,_rs+1);
        int rs = atoi(_rs);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        //immediate
        int immediate = atoi(instr[3]);
        int total = (opcode<<26) | (rs<<21) | (rd<<16) | (immediate&0xFFFF);
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"andi")){//andi
        int opcode = 12;
        //rs
        char* _rs = instr[2];
        strcpy(_rs,_rs+1);
        int rs = atoi(_rs);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        //immediate
        int immediate = atoi(instr[3]);
        int total = (opcode<<26) | (rs<<21) | (rd<<16) | (immediate&0xFFFF);
        
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"add")){//add
        int opcode = 0;
        int func = 32;
        //rs1
        char* _rs1 = instr[2];
        strcpy(_rs1,_rs1+1);
        int rs1 = atoi(_rs1);
        //rs2
        char* _rs2 = instr[3];
        strcpy(_rs2,_rs2+1);
        int rs2 = atoi(_rs2);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        
        int total = ((opcode&0x3F)<<26) | ((rs1&0x1F)<<21) | ((rs2&0x1F)<<16) | ((rd&0x1F)<<11) | (func&0x7FF);
        
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"sub")){//sub
        int opcode = 0;
        int func = 34;
        //rs1
        char* _rs1 = instr[2];
        strcpy(_rs1,_rs1+1);
        int rs1 = atoi(_rs1);
        //rs2
        char* _rs2 = instr[3];
        strcpy(_rs2,_rs2+1);
        int rs2 = atoi(_rs2);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        int total = ((opcode&0x3F)<<26) | ((rs1&0x1F)<<21) | ((rs2&0x1F)<<16) | ((rd&0x1F)<<11) | (func&0x7FF);
        
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"and")){//and
        int opcode = 0;
        int func = 36;
        //rs1
        char* _rs1 = instr[2];
        strcpy(_rs1,_rs1+1);
        int rs1 = atoi(_rs1);
        //rs2
        char* _rs2 = instr[3];
        strcpy(_rs2,_rs2+1);
        int rs2 = atoi(_rs2);
        //rd
        char* _rd = instr[1];
        strcpy(_rd,_rd+1);
        int rd = atoi(_rd);
        int total = ((opcode&0x3F)<<26) | ((rs1&0x1F)<<21) | ((rs2&0x1F)<<16) | ((rd&0x1F)<<11) | (func&0x7FF);
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"beqz")){//beqz
        int opcode = 4;
        //rs
        char* _rs = instr[1];
        strcpy(_rs,_rs+1);
        int rs = atoi(_rs);
        //rd
        int rd = 0;
        //immediate
        //判断immediate字段是否为立即数
        bool is_immediate = true;
        for(int i = 0; i<strlen(instr[2]); i++){
            if(instr[2][i]<'0'||instr[2][i]>'9'){
                is_immediate = false;
            }
        }
        int immediate = 0;
        if(!is_immediate){//immediate字段是标签
            int mark_address = 0;
            for(int i=0;i<markSymbolContainerLen;i++){
                if(!strcmp(instr[2],markSymbolContainer[i]->markName)){ 
                    mark_address = markSymbolContainer[i]->addressCounter;
                }
            }
            immediate = mark_address - address - 1;
        }else{
            immediate = atoi(instr[2]);
        }
        int total = ((opcode&0x3F)<<26) | ((rs&0x1F)<<21) | ((rd&0x1F)<<16) | (immediate&0xFFFF);
        
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"j")){//j
        int opcode = 2;
        //immediate
        //判断immediate字段是否为立即数
        bool is_immediate = true;
        for(int i = 0; i<strlen(instr[1]); i++){
            if(instr[1][i]<'0'||instr[1][i]>'9'){
                is_immediate = false;
            }
        }
        int immediate = 0;
        if(!is_immediate){//immediate字段是标签
            int mark_address = 0;
            for(int i=0;i<markSymbolContainerLen;i++){
                if(!strcmp(instr[1],markSymbolContainer[i]->markName)){ 
                    mark_address = markSymbolContainer[i]->addressCounter;
                }
            }
            immediate = mark_address - address - 1;
        }else{
            immediate = atoi(instr[1]);
        }
        int total = ((opcode&0x3F)<<26) | (immediate&0x3FFFFFF);
        
        itoa(total,str,10);
    }else if(!strcmp(instr[0],"halt")){//halt
        int opcode = 1;
        int immediate = 0;
        int total = ((opcode&0x3F)<<26) | (immediate&0x3FFFFFF);
        
        itoa(total,str,10);
    }
    else if(!strcmp(instr[0],"noop")){//noop
        int opcode = 3;
        int immediate = 0;
        int total = ((opcode&0x3F)<<26) | (immediate&0x3FFFFFF);
        
        itoa(total,str,10);
    }
}

int main(int argc, char *argv[]){

    instructionContainer = (instructionEntry **) malloc(1000*sizeof(instructionEntry*));
    markSymbolContainer = (markSymbol **) malloc(1000*sizeof(markSymbol*));
    
    markSymbolContainerLen = 0;
    instructionContainerLen = 0;

    FILE *inFilePtr;
    FILE *outFilePtr;
    char line[1000];

    if (argc !=3) {
        printf("error:usage: %s <asm file> <machine-code file>\n", argv[0]);
        system("pause");
        exit(1);
    }

    inFilePtr = fopen(argv[1],"r");
    if (inFilePtr == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        system("pause");
        exit(1);
    }
    outFilePtr = fopen(argv[2],"w+");

    int done = 0;
    int counter = 0;
    while(!done){
        if (fgets(line, 1000, inFilePtr) == NULL){
            done = 1;
        }
        else {
            //printf("%d: ", counter);
            char *content;

            // 去掉该行字符串分号及分号后所有内容
            content = strtok(line,";");
            // 去掉改行末尾换行符
            content = strtok(content,"\n");

            char *buf[5], *p;
            //按空格分割该行字符串
            int out=0;
            p = strtok(content," ");
            while(p){
                buf[out]=p;
                out++;
                p = strtok(NULL, " ");
            }
            //按分号分割该行字符串
            char *temp[5];
            int len = 0;
            for(int i=0; i<out; i++){
                p = strtok(buf[i],",");
                while(p){
                    temp[len]=p;
                    len++;
                    p = strtok(NULL, ",");
                }
            }
            //将整理完的指令加入指令容器里
            instructionContainer[counter] = (instructionEntry*) malloc(sizeof(instructionEntry));
            instructionContainer[counter]->len = len;
            for(int i=0; i<len; i++){
                instructionContainer[counter]->item[i] = (char*) malloc(10*sizeof(char));
                strcpy(instructionContainer[counter]->item[i],temp[i]);
            }
            
            // 第一个符号不在指令符号集里的情况
            if(!lookup(temp[0],symbol,11)){
                markSymbolContainer[markSymbolContainerLen] = (markSymbol*) malloc(sizeof(markSymbol));
                markSymbolContainer[markSymbolContainerLen] -> markName = (char*) malloc(10*sizeof(char));
                strcpy(markSymbolContainer[markSymbolContainerLen] -> markName,temp[0]);
                markSymbolContainer[markSymbolContainerLen] -> addressCounter = counter;
                markSymbolContainerLen++;
            }
            //printf("\n");
        }
        counter++;
    }
    instructionContainerLen = counter-1;
    
    printf("************ instructionContainer info ************\n");
    printf("\n");
    printf("instructionContainerLen is: %d\n", instructionContainerLen);
    for(int i=0;i<instructionContainerLen; i++){
        printf("%d: ", i);
        for(int j=0; j<instructionContainer[i]->len; j++){
            printf(" %s",instructionContainer[i]->item[j]);
        }
        printf("\n");
    }
    printf("\n\n");
    printf("************ markSymbolContainer info ************\n");
    printf("\n");
    printf("markSymbolContainerLen is: %d\n", markSymbolContainerLen);
    for(int i=0;i<markSymbolContainerLen; i++){
        printf("%d: ", i);
        printf("name is: %s,", markSymbolContainer[i]->markName);
        printf("  address is: %d\n",markSymbolContainer[i]->addressCounter);
    }
    printf("\n\n");

    printf("****************** machine-code ******************\n");
    printf("\n");
    for(int i=0; i<instructionContainerLen; i++){
        char* first_symbol = malloc(10*sizeof(char));
        strcpy(first_symbol,instructionContainer[i]->item[0]);

        if(lookup(first_symbol,symbol,11)){
            /* 第一个符号是指令符号 */
            int temp_len = instructionContainer[i]->len;
            char* temp_instr[temp_len];
            for(int j=0; j<temp_len; j++){
                temp_instr[j] = instructionContainer[i]->item[j];
            }
            //指令合法性检查
            if(!legal_check(temp_instr,temp_len)){
                printf("assemble instruction at address %d is illegal",i);
                exit(1);
            }
            
            char* str_num = malloc(32*sizeof(char));
            turn_assemble_to_machinecode(temp_instr, str_num,i);
            printf("machine-code is : %s\n", str_num); 
            fputs(str_num, outFilePtr);
            fputs("\n",outFilePtr);
        }else{
            /* 第一个符号是标签 */
            int temp_len = instructionContainer[i]->len-1;
            char* temp_instr[temp_len-1];
            for(int j=0; j<temp_len; j++){
                temp_instr[j] = instructionContainer[i]->item[j+1];
            }
            //指令合法性检查
            if(!legal_check(temp_instr,temp_len)){
                printf("assemble instruction at address %d is illegal",i);
                exit(1);
            }
            char* str_num = malloc(32*sizeof(char));
            turn_assemble_to_machinecode(temp_instr, str_num,i);
            printf("machine-code is : %s\n", str_num);
            fputs(str_num, outFilePtr);
            fputs("\n",outFilePtr);
        }
    }
}
