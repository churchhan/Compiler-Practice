/* CS5363 Project: Complier for TL language
Finished by: Jin Han  Sni550 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int lineNum = 0;
int tokenid = 0;
int errorid = 0;
int g_viarable_id = 0;
int paserpointer = 0;
int pointer_next = 0;
int node_number = 4;
int parent_node_number;
int relationid = 0;
int cfg_node_id = 0;
int block_id = 1;
int g_reg_id = 0;
int sematic_error = 0;
char word[30];
char file_name[50];
char ast_name[50];
char cfg_name[50];
char ass_name[50];
char ass_name_o[50];
char reg_id[4];
FILE *SourcefPtr;
FILE *lexicaloutput;
FILE *scannererror;
FILE *paseroutput;
FILE *pasererror;
FILE *cfgoutput;
FILE *codeoutput;
FILE *codeoutput_o;


struct return_node{
    int number;
    char type[10];
};
struct return_node return_node1;

struct tokenrecord {
    char name[30];
    char value[30];
    int  line;
};
struct tokenrecord temp_record;
struct tokenrecord token_list[300];

struct errorrecord {
    char name[30];
    char info[40];
    int  line;
};
struct errorrecord error_list[20];

struct globalviarable {
    char name[30];
    char viatype[10];
};
struct globalviarable g_viarable_list[30];


struct node{
    char content[30];
    char type[10];
    char color[10];
    int level;
};
struct node node_list[300];
struct node temp_node_list[300];

struct id_node{
    char content[30];
    char type[10];
    char color[10];
};
struct id_node id_node_list[300];

struct op_node{
    char content[30];
    char type[10];
    char color[10];
    int  level;
};
struct op_node op_node_list[300];

struct cfg_node{
    int id;
    char name[30];
    char value[30];
    int parent_id;
    int left_side;
};
struct cfg_node cfg_node_list[300];

struct block_relation{
    int parent;
    int child;
};
struct block_relation b_relation_list[100];

struct t_address_code{
    int block_id;
    char operator[30];
    char operand1[30];
    int  opd1;
    char operand2[30];
    int  opd2;
    char destination[30];
    int  dest1;
    char destination2[30];
    int  dest2;
};
struct t_address_code t_code_list[300];

int t_code_id = 0;
int t_reg_id = 0;

struct g_reg{
    char g_var[30];
    int pivor;
};
struct g_reg g_reg_list[30];

struct c_pro{
    char var_name[30];
    int value;
};
struct c_pro c_pro_list[30];
int c_pro_id = 0;

//==================================================================
//===========================subfunction============================
void checkvalue(char *word ) {
    int count = 0;

    //printf("test in checkvalue %s \n", word);
    
    if (strcmp(word, "if") == 0) {strcpy(token_list[tokenid].name , "IF");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "then") == 0) {strcpy(token_list[tokenid].name , "THEN");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "else") == 0) {strcpy(token_list[tokenid].name , "ELSE");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "begin") == 0) {strcpy(token_list[tokenid].name , "BEGIN");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "end") == 0) {strcpy(token_list[tokenid].name , "END");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    
    else if (strcmp(word, "while") == 0) {strcpy(token_list[tokenid].name , "WHILE");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "do") == 0) {strcpy(token_list[tokenid].name , "DO");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "program") == 0) {strcpy(token_list[tokenid].name , "PROGRAM");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "var") == 0) {strcpy(token_list[tokenid].name , "VAR");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "as") == 0) {strcpy(token_list[tokenid].name , "AS");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "int") == 0) {strcpy(token_list[tokenid].name , "INT");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "bool") == 0) {strcpy(token_list[tokenid].name , "BOOL");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "writeint") == 0) {strcpy(token_list[tokenid].name , "WRITEINT");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    else if (strcmp(word, "readint") == 0) {strcpy(token_list[tokenid].name , "READINT");
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
        tokenid++;}
    
    
    else if (strcmp(word, "div") == 0) {strcpy(token_list[tokenid].name , "MULTIPLICATIVE");
        token_list[tokenid].line=lineNum;
        strcpy(token_list[tokenid].value , "div");
        fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
        tokenid++;}
    
    else if (strcmp(word, "mod") == 0) {strcpy(token_list[tokenid].name , "MULTIPLICATIVE");
        token_list[tokenid].line=lineNum;
        strcpy(token_list[tokenid].value , "mod");
        fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
        tokenid++;}
    
    else if (strcmp(word, "false") == 0) {strcpy(token_list[tokenid].name , "boollit");
        token_list[tokenid].line=lineNum;
        strcpy(token_list[tokenid].value , "false");
        fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
        tokenid++;}
    
    else if (strcmp(word, "true") == 0) {strcpy(token_list[tokenid].name , "boollit");
        token_list[tokenid].line=lineNum;
        strcpy(token_list[tokenid].value , "true");
        fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
        tokenid++;}
    
    else{
    while (word[count]!='\0') {
        if ((word[count]>='A' && word[count]<='Z') || isdigit(word[count])) {
            count++;
        }
        else{
            goto idendabnormal;
        }
        
    }
        goto idendnormal;
        
    idendabnormal: strcpy(error_list[errorid].name, word);
    strcpy(error_list[errorid].info , "is illegal please check it");
    error_list[errorid].line=lineNum;
    fprintf(scannererror,"ERROR:%s %s in line %d \n",error_list[errorid].name,error_list[errorid].info,error_list[errorid].line);
       errorid++;
        
        goto endident;
        
    idendnormal: strcpy(token_list[tokenid].name , "ident");
        strcpy(token_list[tokenid].value , word);
        token_list[tokenid].line=lineNum;
        fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
        tokenid++;
        
    endident: ;
        
    }
    
}



int lexicalscanner(FILE *SourcefPtr) {
    char char_checking;
    char next_char;
    int i=0;
    int j=0;
    error_list[0].name[0]='0';
    
    while ((char_checking = fgetc(SourcefPtr)) != EOF) {
        
        // Handle comment
        if (char_checking == '%') {
            while ((char_checking = fgetc(SourcefPtr)) != '\n') {}
            lineNum++;
        }
        if (char_checking == ' ') {
            
        }
        
        if (char_checking == ';') {
            strcpy(token_list[tokenid].name , "SC");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
            
            tokenid++;
            
        }
        
        if (char_checking == '(') {
            strcpy(token_list[tokenid].name , "LP");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
            
            tokenid++;
        }
        
        if (char_checking == ')') {
            strcpy(token_list[tokenid].name , "RP");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
            
            tokenid++;
        }
        
        if (char_checking == '*') {
            strcpy(token_list[tokenid].name , "MULTIPLICATIVE");
            strcpy(token_list[tokenid].value , "*");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
            
            tokenid++;
        }
        
        if (char_checking == '+') {
            strcpy(token_list[tokenid].name , "ADDITIVE");
            strcpy(token_list[tokenid].value , "+");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
            
            tokenid++;
        }
        
        if (char_checking == '-') {
            strcpy(token_list[tokenid].name , "ADDITIVE");
            strcpy(token_list[tokenid].value , "-");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
            
            tokenid++;
        }
        
        if (char_checking == '\n')
            lineNum=lineNum+1;
        
        if (char_checking == '=') {
            strcpy(token_list[tokenid].name , "COMPARE");
            strcpy(token_list[tokenid].value , "=");
            token_list[tokenid].line=lineNum;
            
            fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
            
            tokenid++;
        }
        
        if (char_checking == '!') {
            if ((char_checking = fgetc(SourcefPtr)) == '=') {
                strcpy(token_list[tokenid].name , "COMPARE");
                strcpy(token_list[tokenid].value , "!=");
                token_list[tokenid].line=lineNum;
                fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
                
                tokenid++;
            }
            else{
                fseek(SourcefPtr, -1, SEEK_CUR);
                strcpy(error_list[errorid].name, "!");
                strcpy(error_list[errorid].info, " = is missing after ! ");
                error_list[errorid].line=lineNum;
                fprintf(scannererror,"ERROR: = is missing after %s in line%d \n",error_list[errorid].name,error_list[errorid].line);
                errorid++;
            }
            
        }
        
        
        if (char_checking == ':') {
            if ((char_checking = fgetc(SourcefPtr)) == '=') {
                strcpy(token_list[tokenid].name , "ASGN");
                
                fprintf(lexicaloutput,"%s \n",token_list[tokenid].name);
                token_list[tokenid].line=lineNum;
                
                i = 0;
                tokenid++;
            }
            else{
                fseek(SourcefPtr, -1, SEEK_CUR);
                strcpy(error_list[errorid].name, ":");
                strcpy(error_list[errorid].info, " = is missing after : ");
                error_list[errorid].line=lineNum;
                fprintf(scannererror,"ERROR: = is missing after %s in line%d \n",error_list[errorid].name,error_list[errorid].line);

                errorid++;
            }
            
        }
        
        if (char_checking == '<') {
            if ((char_checking = fgetc(SourcefPtr)) == '=') {
                strcpy(token_list[tokenid].name , "COMPARE");
                strcpy(token_list[tokenid].value , "<=");
                token_list[tokenid].line=lineNum;
                fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
                
                tokenid++;
            }
            else{
                fseek(SourcefPtr, -1, SEEK_CUR);
                strcpy(token_list[tokenid].name , "COMPARE");
                strcpy(token_list[tokenid].value , "<");
                token_list[tokenid].line=lineNum;
                fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
                
                tokenid++;
            }
            
        }
        
        if (char_checking == '>') {
            if ((char_checking = fgetc(SourcefPtr)) == '=') {
                strcpy(token_list[tokenid].name , "COMPARE");
                strcpy(token_list[tokenid].value , ">=");
                token_list[tokenid].line=lineNum;
                fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
                
                tokenid++;
            }
            else{
                fseek(SourcefPtr, -1, SEEK_CUR);
                strcpy(token_list[tokenid].name , "COMPARE");
                strcpy(token_list[tokenid].value , ">");
                token_list[tokenid].line=lineNum;
                fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
                
                tokenid++;
            }
            
        }
        
        
        if (isdigit(char_checking)){
            temp_record.value[i++] = char_checking;
            while (isdigit(next_char = fgetc(SourcefPtr)) || isalpha(next_char)) {
                temp_record.value[i++] = next_char;
            }
            fseek(SourcefPtr, -1, SEEK_CUR);
            temp_record.value[i] = '\0';
            
            for (j=0; j<i; j++) {
                if (!(isdigit(temp_record.value[j]))) {
                    goto errorstate;
                }
            }
            
            strcpy(token_list[tokenid].name , "num");
            for (j=0; j<=i; j++) {
                token_list[tokenid].value[j]=temp_record.value[j];
            }
            token_list[tokenid].line=lineNum;
            fprintf(lexicaloutput,"%s(%s) \n",token_list[tokenid].name,token_list[tokenid].value);
            //printf("%s<%s> \n", token_list[tokenid].name,token_list[tokenid].value);
            
            i=0;
            tokenid++;
            
            goto endstate;
            
        errorstate:
            for (j=0; j<=i ; j++) {
                error_list[errorid].name[j]=temp_record.value[j];
                temp_record.value[j]=0;
            }
            error_list[errorid].line=lineNum;
            strcpy(error_list[errorid].info , "Character in num ");
            fprintf(scannererror,"ERROR: %s in line%d, character in num \n",error_list[errorid].name,error_list[errorid].line);
            //printf("ERROR: %s in line%d, should not have character in num. \n",error_list[errorid].name,error_list[errorid].line);
            
            i=0;
            errorid++;
            
        }// end check with num
        
        else if (isalpha(char_checking)) {
            temp_record.value[i++] = char_checking;
            while ( isalpha(next_char = fgetc(SourcefPtr)) || isdigit(next_char) ) {
                temp_record.value[i++] = next_char;
                }
            
            fseek(SourcefPtr, -1, SEEK_CUR);
            temp_record.value[i] = '\0';

            checkvalue(temp_record.value);
            
            i = 0;
            
        }
        
        
        //==================
    endstate: ; // End state
        
        
        
        
    }
    
    printf("\n------lexical scanner is finished. total is %d lines. -------\n", lineNum);
    
    return lineNum;
    
   
    
}

//======================================================

int get_r_index(int id){
    int p=0;
    while (p<cfg_node_id) {
        if (cfg_node_list[p].parent_id==id && cfg_node_list[p].left_side!= 1 ) {
            break;
        }
        p++;
    }
    return p;
}

int get_l_index(int id){
    int p=0;
    while (p<cfg_node_id) {
        if (cfg_node_list[p].parent_id==id && cfg_node_list[p].left_side== 1 ) {
            break;
        }
        p++;
    }
    return p;
}

int idtoindex(int id){
    int p=0;
    while (p<cfg_node_id) {
        if (cfg_node_list[p].id==id) {
            break;
        }
        p++;
    }
    return p;
}

void inttoreg_id(int id){
    
    int hundred,ten,digit;
    char hun[2],te[2],di[2];
    strcpy(reg_id,"\0");
    hundred=id/100;
    if (hundred!=0) {
        hun[0]=hundred+'0';
        hun[1]='\0';
        strcat(reg_id,hun);
        //printf("reg_id:%s",reg_id);
    }
    
    ten=(id-hundred*100)/10;
    if (ten!=0) {
        te[0]=ten+'0';
        te[1]='\0';
        strcat(reg_id,te);
    }
    
    digit=id-hundred*100-ten*10;
    
    di[0]=digit+'0';
    di[1]='\0';
    //printf("di %s\n",di);
    strcat(reg_id,di);
    //printf("reg_id:%d %s %s %s \n",id,te,di,reg_id);
    
}

int regtoadd(char reg[]){
    int s=1;
    int r[3]={0,0,0};
    int result =0;
    while (reg[s]!='\0') {
        r[s-1]=reg[s]-'0';
        if(s==2){
            r[0]=r[0]*10;
        }
        else if(s==3){
            r[0]=r[0]*10;
            r[1]=r[1]*10;
        }
        s++;
    }
    result=r[0]+r[1]+r[2];
    return result;
    
}

int chartoint(char array[]){
    int s=0;
    int r[7]={0,0,0,0,0,0,0};
    int result=0;
    int k,j;
    while (array[s]!='\0') {
        r[s]=array[s]-'0';
        for (k=0; k<s; k++) {
            r[k]=r[k]*10;
        }
        s++;
    }
    for (j=0; j<7; j++) {
        result=result+r[j];
    }
    return result;
}

int allregtoadd(char reg[], int base){
    int g_pivor;
    int s;
    if (strncmp(reg,"r_",2)==0) {
        for (s=0; s<g_reg_id; s++) {
            if (strcmp(reg,g_reg_list[s].g_var)==0) {
                g_pivor = s;
                break;
            }
        }
        // find  variable address
    }
    else {
        g_pivor=base+regtoadd(reg);
    }
    
    return g_pivor;
}

//=======================================================start of paser procedure=============
struct return_node exp_handler(int handler_start, int handler_end){
    struct return_node handler_return, top_return,left_return,right_return;
    int start,end,pivor;
    int i,count;
    int lp_number,rp_number;
    int compare_number=0;
    int compare_position;
    int previous_op_number=0;
    int handler_node_number;
    int toppest_node_number;
    
    struct find_aandm {
        int position;
    };
    struct find_aandm aandm_list[50];
    
    int count_aandm=0;
    
    int find_aandm=0;
    int lpinfind;
    
    char handler_node_type[10]="0";
    char color[10];
    
    //=========check compare=======
    start=handler_start;
    end=handler_end;
    
    for(i=start;i<=end;i++){
        if(strcmp(token_list[i].name,"COMPARE")==0){
            compare_number=1;
            compare_position=i;
            break;
        }
    }
    
    i=handler_start;
    while(i<=handler_end){
        if(strcmp(token_list[i].name,"ADDITIVE")==0 || strcmp(token_list[i].name,"MULTIPLICATIVE")==0){
            count_aandm++;
            aandm_list[count_aandm].position=i;
            //printf("count_aandm:%d:%s\n",aandm_list[count_aandm].position,token_list[aandm_list[count_aandm].position].name);
            if (count_aandm==4){
                break;

            }
        }
        
        if (strcmp(token_list[i].name,"LP")==0){
            lpinfind=1;
            i++;
            while(lpinfind>0){
                if(strcmp(token_list[i].name,"LP")==0){
                    lpinfind++;
                }
                else if (strcmp(token_list[i].name,"RP")==0){
                    lpinfind--;
                }
                i++;
            }
            i--;
        }
        i++;
    }
    
    
    
    if(compare_number!=0){
        left_return=exp_handler(handler_start,compare_position-1);
        right_return=exp_handler(compare_position+1,handler_end);
        if(strcmp(left_return.type,right_return.type)==0){
            strcpy(color,"white");
        }
        else{
            strcpy(color,"red");
        }
        fprintf(paseroutput,"  n%d [label=\"%s:BOOL\",fillcolor=\"%s\",shape=box] \n",compare_position,token_list[compare_position].value,color);
        fprintf(paseroutput,"  n%d -> n%d \n", compare_position,left_return.number);
        fprintf(paseroutput,"  n%d -> n%d \n", compare_position,right_return.number);
        handler_return.number=compare_position;
        strcpy(handler_return.type,"BOOL");
        
    }
    else{
        if(count_aandm<=3){
            
                pivor=start;
                while(pivor<=end){
                    if (pivor==end){
                        if (pivor==start){   //if it is the only node
                            if (strcmp(token_list[pivor].name,"ident")==0){
                                strcpy(id_node_list[pivor].color,"red");
                                strcpy(id_node_list[pivor].content,token_list[pivor].value);
                                for (count=0;count<g_viarable_id;count++){
                                    if(strcmp(id_node_list[pivor].content,g_viarable_list[count].name)==0){
                                        strcpy(id_node_list[pivor].color,"white");
                                        strcpy(id_node_list[pivor].type,g_viarable_list[count].viatype);
                                    }
                                }
                                handler_node_number=pivor;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                                handler_return.number=handler_node_number;
                                strcpy(handler_return.type,id_node_list[handler_node_number].type);
                                return handler_return;
                            }
                            else if(strcmp(token_list[pivor].name,"num")==0){
                                strcpy(id_node_list[pivor].content,token_list[pivor].value);
                                strcpy(id_node_list[pivor].type,"INT");
                                strcpy(id_node_list[pivor].color,"white");
                                handler_node_number=pivor;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                                handler_return.number=handler_node_number;
                                strcpy(handler_return.type,id_node_list[handler_node_number].type);
                                return handler_return;
                            }
                            else if(strcmp(token_list[pivor].name,"boollit")==0){
                                strcpy(id_node_list[pivor].content,token_list[pivor].value);
                                strcpy(id_node_list[pivor].type,"BOOL");
                                strcpy(id_node_list[pivor].color,"white");
                                handler_node_number=pivor;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                                handler_return.number=handler_node_number;
                                strcpy(handler_return.type,id_node_list[handler_node_number].type);
                                return handler_return;
                            }
                        }
                        else{   //if it is the last node
                            
                            if (strcmp(token_list[pivor].name,"ident")==0){
                                strcpy(id_node_list[pivor].color,"red");
                                strcpy(id_node_list[pivor].content,token_list[pivor].value);
                                for (count=0;count<g_viarable_id;count++){
                                    if(strcmp(id_node_list[pivor].content,g_viarable_list[count].name)==0){
                                        strcpy(id_node_list[pivor].color,"white");
                                        strcpy(id_node_list[pivor].type,g_viarable_list[count].viatype);
                                    }
                                }
                                handler_node_number=pivor;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                                fprintf(paseroutput,"  n%d -> n%d \n", previous_op_number,handler_node_number);
                            }
                            else if(strcmp(token_list[pivor].name,"num")==0){
                                
                                strcpy(id_node_list[pivor].content,token_list[pivor].value);
                                
                                strcpy(id_node_list[pivor].type,"INT");
                                strcpy(id_node_list[pivor].color,"white");
                                handler_node_number=pivor;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                                fprintf(paseroutput,"  n%d -> n%d \n", previous_op_number,handler_node_number);
                            }
                            else if(strcmp(token_list[pivor].name,"boollit")==0){
                                strcpy(id_node_list[pivor].content,token_list[pivor].value);
                                strcpy(id_node_list[pivor].type,"BOOL");
                                strcpy(id_node_list[pivor].color,"white");
                                handler_node_number=pivor;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                                fprintf(paseroutput,"  n%d -> n%d \n", previous_op_number,handler_node_number);
                            }
                            
                        }
                        
                    }//finish handle only one node or it is the last node
                    
                    else{
                        if (strcmp(token_list[pivor].name,"ident")==0){
                            strcpy(id_node_list[pivor].color,"red");
                            strcpy(id_node_list[pivor].content,token_list[pivor].value);
                            for (count=0;count<g_viarable_id;count++){
                                if(strcmp(id_node_list[pivor].content,g_viarable_list[count].name)==0){
                                    strcpy(id_node_list[pivor].color,"white");
                                    strcpy(id_node_list[pivor].type,g_viarable_list[count].viatype);
                                }
                            }
                            handler_node_number=pivor;
                            fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                        }
                        else if(strcmp(token_list[pivor].name,"num")==0){
                            strcpy(id_node_list[pivor].content,token_list[pivor].value);
                            strcpy(id_node_list[pivor].type,"INT");
                            strcpy(id_node_list[pivor].color,"white");
                            handler_node_number=pivor;
                            fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                        }
                        else if(strcmp(token_list[pivor].name,"boollit")==0){
                            strcpy(id_node_list[pivor].content,token_list[pivor].value);
                            strcpy(id_node_list[pivor].type,"BOOL");
                            strcpy(id_node_list[pivor].color,"white");
                            handler_node_number=pivor;
                            fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",handler_node_number,id_node_list[handler_node_number].content,id_node_list[handler_node_number].type,id_node_list[handler_node_number].color);
                        }
                        else if(strcmp(token_list[pivor].name,"LP")==0){
                            lp_number=1;
                            count=pivor+1;
                            //printf("Detected LP.\n");
                            while(lp_number>0){
                                if(strcmp(token_list[count].name,"LP")==0){
                                    lp_number++;
                                }
                                else if (strcmp(token_list[count].name,"RP")==0){
                                    lp_number--;
                                }
                                count++;
                            }
                            
                            top_return=exp_handler(pivor+1,count-2);
                            
                            handler_node_number=top_return.number;
                            strcmp(handler_node_type,top_return.type);
                            pivor=count-1;
                        }
                        
                        //handle coming op
                        
                        
                        if (strcmp(token_list[pivor+1].name,"ADDITIVE")==0 || strcmp(token_list[pivor+1].name,"MULTIPLICATIVE")==0){
                            strcpy(op_node_list[pivor+1].content,token_list[pivor+1].value);
                            strcpy(op_node_list[pivor+1].type,"INT");
                            if(strcmp(token_list[pivor+1].name,"ADDITIVE")==0){
                                op_node_list[pivor+1].level=0;
                            }
                            else{
                                op_node_list[pivor+1].level=1;
                            }
                            
                            if (previous_op_number==0){
                                previous_op_number=pivor+1;
                                toppest_node_number=pivor+1;
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",pivor+1,op_node_list[pivor+1].content,op_node_list[pivor+1].type,"white");
                                fprintf(paseroutput,"  n%d -> n%d \n", pivor+1,handler_node_number);
                            }
                            else{
                                //printf("%d,%s\n",pivor+1,token_list[pivor+1].value);
                                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",pivor+1,op_node_list[pivor+1].content,op_node_list[pivor+1].type,"white");
                                
                                if(op_node_list[pivor+1].level<=op_node_list[previous_op_number].level){
                                    toppest_node_number=pivor+1;
                                    fprintf(paseroutput,"  n%d -> n%d \n", previous_op_number,handler_node_number);
                                    fprintf(paseroutput,"  n%d -> n%d \n", pivor+1,previous_op_number);
                                    previous_op_number=pivor+1;
                                }
                                else{
                                    toppest_node_number=previous_op_number;
                                    fprintf(paseroutput,"  n%d -> n%d \n", pivor+1,handler_node_number);
                                    fprintf(paseroutput,"  n%d -> n%d \n", previous_op_number,pivor+1);
                                    previous_op_number=pivor+1;
                                }
                            }
                            
                            
                        }
                        else{
                            printf("Wrong expression. Please check the line %d.", token_list[pivor+1].line);
                            handler_return.number=-1;
                            return handler_return;
                        }
                        
                    }
                    
                    pivor=pivor+2;
                    
                }//end of while
                
                handler_return.number=toppest_node_number;
                strcpy(handler_return.type,op_node_list[toppest_node_number].type);
                
                
            
        }
    
    else{
        if (strcmp(token_list[aandm_list[count_aandm].position].name,"ADDITIVE")==0){
            find_aandm=aandm_list[count_aandm].position;
            //printf("find_aandm:%d,%s",find_aandm,token_list[find_aandm].name);
            
        }
        else if (strcmp(token_list[aandm_list[count_aandm-1].position].name,"ADDITIVE")==0) {
            find_aandm=aandm_list[count_aandm-1].position;
            //printf("find_aandm:%d,%s",find_aandm,token_list[find_aandm].name);
           
        }
        else if (strcmp(token_list[aandm_list[count_aandm-2].position].name,"ADDITIVE")==0){
            find_aandm=aandm_list[count_aandm-2].position;
            //printf("find_aandm:%d,%s",find_aandm,token_list[find_aandm].name);
            
        }
        else if (strcmp(token_list[aandm_list[count_aandm-3].position].name,"ADDITIVE")==0){
            find_aandm=aandm_list[count_aandm-3].position;
            //printf("find_aandm:%d,%s",find_aandm,token_list[find_aandm].name);
            
        }
        else {
            find_aandm=aandm_list[count_aandm].position;
            //printf("find_aandm:%d,%s",find_aandm,token_list[find_aandm].name);
           
        }
        
        left_return=exp_handler(handler_start,find_aandm-1);
        right_return=exp_handler(find_aandm+1,handler_end);
        if(strcmp(left_return.type,right_return.type)==0){
            strcpy(color,"white");
        }
        else{
            strcpy(color,"red");
        }
        fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",find_aandm,token_list[find_aandm].value,right_return.type,color);
        fprintf(paseroutput,"  n%d -> n%d \n", find_aandm,left_return.number);
        fprintf(paseroutput,"  n%d -> n%d \n", find_aandm,right_return.number);
        handler_return.number=find_aandm;
        strcpy(handler_return.type,right_return.type);
    }
    }

    return handler_return;
}





struct return_node paser_expression(int exp_start, int exp_end, int parent_node_number){
    int judgement = 1 ;
    int result;
    int count_pivor=exp_start;
    int cal_previous=0;
    int judge3=0;
    int temp_id;
    int b;
    struct return_node return_exp;
    while(count_pivor<=exp_end){
        if(strcmp(token_list[count_pivor].name,"num")==0){
            switch(cal_previous){
                case 0 : result=chartoint(token_list[count_pivor].value);break;
                case 1 : result=result+chartoint(token_list[count_pivor].value);break;
                    case 2 : result=result-chartoint(token_list[count_pivor].value);break;
                    case 3 : result=result*chartoint(token_list[count_pivor].value);break;
                    case 4 : result=result/chartoint(token_list[count_pivor].value);break;
                    case 5 : result=result%chartoint(token_list[count_pivor].value);break;
            }
        }
        else if (strcmp(token_list[count_pivor].name,"ident")==0){
            for(b=0;b<c_pro_id;b++){
                if(strcmp(token_list[count_pivor].value,c_pro_list[b].var_name)==0){
                    judge3=1;
                    temp_id=b;
                    break;
                }
            }
            
            if(judge3==1){
                switch(cal_previous){
                    case 0 : result=c_pro_list[temp_id].value;break;
                    case 1 : result=result+c_pro_list[temp_id].value;break;
                    case 2 : result=result-c_pro_list[temp_id].value;break;
                    case 3 : result=result*c_pro_list[temp_id].value;break;
                    case 4 : result=result/c_pro_list[temp_id].value;break;
                    case 5 : result=result%c_pro_list[temp_id].value;break;
                }
            }
            else{
                judgement=0;
                break;
            }
            
        }
        else if (strcmp(token_list[count_pivor].name,"ADDITIVE")==0){
            if(strcmp(token_list[count_pivor].value,"+")==0){
                cal_previous=1;
            }
            else{
                cal_previous=2;
            }
            
        }
        else if (strcmp(token_list[count_pivor].name,"MULTIPLICATIVE")==0){
            if(strcmp(token_list[count_pivor].value,"*")==0){
                cal_previous=3;
            }
            else if (strcmp(token_list[count_pivor].value,"/")==0){
                cal_previous=4;
            }
            else{
                cal_previous=5;
            }
        }
        else if (strcmp(token_list[count_pivor].name,"COMPARE")==0){
            judgement=0;
            break;
        }
        count_pivor++;
    }
    
    
    if(judgement ==1){
        inttoreg_id(result);
        fprintf(paseroutput,"  n%d [label=\"%s:%s\",shape=box] \n",exp_start,reg_id,"INT");
        printf("inttoreg_id: %d, %s", result, reg_id);
        cfg_node_list[cfg_node_id].id=exp_start;
        strcpy(cfg_node_list[cfg_node_id].name,"num");
        strcpy(cfg_node_list[cfg_node_id].value,reg_id);
        cfg_node_list[cfg_node_id].parent_id=parent_node_number;
        cfg_node_id++;
        
        //printf("%d\n",exp_start);
        return_exp.number=exp_start;
        strcpy(return_exp.type,"INT");
        return (return_exp);
        goto foroptimization;
    }
    
    int start,end;
    
    start=exp_start;
    end=exp_end;
    
    int count;
    int base_line;
    int op_number,id_number;
    int temp_node_id=100;
    int lp_number=0;
    int rp_number=0;
    int opandlprp_number;
    int ident_number;
    int han=0;
    
    
    
    //printf("test-break %d, %d\n",start,end);
    do{
        if(strcmp(token_list[start].name,"ident")==0){
            strcpy(id_node_list[start].color,"red");
            strcpy(id_node_list[start].content,token_list[start].value);
            for (count=0;count<g_viarable_id;count++){
                if(strcmp(id_node_list[start].content,g_viarable_list[count].name)==0){
                    strcpy(id_node_list[start].color,"white");
                    strcpy(id_node_list[start].type,g_viarable_list[count].viatype);
                }
            }
            
        }
        else if(strcmp(token_list[start].name,"num")==0){
            strcpy(id_node_list[start].content,token_list[start].value);
            strcpy(id_node_list[start].type,"INT");
            strcpy(id_node_list[start].color,"white");
            
        }
        else if(strcmp(token_list[start].name,"boollit")==0){
            strcpy(id_node_list[start].content,token_list[start].value);
            strcpy(id_node_list[start].type,"BOOL");
            strcpy(id_node_list[start].color,"white");
            
            
        }
        else if(strcmp(token_list[start].name,"COMPARE")==0 ||strcmp(token_list[start].name,"ADDITIVE")==0||strcmp(token_list[start].name,"MULTIPLICATIVE")==0){
            strcpy(op_node_list[start].content,token_list[start].value);
            
        }
        start++;
    }while(start<end+1);
    
    op_number=0;
    for(count=exp_start;count<=exp_end;count++){
        if(op_node_list[count].content[0]!='\0'){
            //printf("op_node_list: %d,%s,%s\n",count,op_node_list[count].content,op_node_list[count].type);
            op_number++;}
    }
    id_number=0;
    for(count=exp_start;count<=exp_end;count++){
        if(id_node_list[count].content[0]!='\0'){
            //printf("op_node_list: %d,%s,%s\n",count,op_node_list[count].content,op_node_list[count].type);
            id_number++;}
    }
    
    //printf("Enter exp.\n");
    if(id_number!=(op_number+1)){
        printf("Wrong expression, pleasse check the line %d. \n",token_list[exp_start].line);
        return_exp.number=-1;
        return return_exp;
    }
    
    
    
    
    if(op_number==0){
        //printf("boollit value: %d, %s.\n",exp_start,id_node_list[exp_start].type);
        fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",exp_start,id_node_list[exp_start].content,id_node_list[exp_start].type,id_node_list[exp_start].color);
        
        cfg_node_list[cfg_node_id].id=exp_start;
        strcpy(cfg_node_list[cfg_node_id].name,token_list[exp_start].name);
        strcpy(cfg_node_list[cfg_node_id].value,token_list[exp_start].value);
        cfg_node_list[cfg_node_id].parent_id=parent_node_number;
        cfg_node_id++;
        
        //printf("%d\n",exp_start);
        return_exp.number=exp_start;
        strcpy(return_exp.type,id_node_list[exp_start].type);
        return (return_exp);
    }
    else if(op_number==1){
        
        for(count=exp_start;count<=exp_end;count++){
            if(id_node_list[count].content[0]!='\0'){
                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",count,id_node_list[count].content,id_node_list[count].type,id_node_list[count].color);
                
                cfg_node_list[cfg_node_id].id=count;
                strcpy(cfg_node_list[cfg_node_id].name,token_list[count].name);
                strcpy(cfg_node_list[cfg_node_id].value,token_list[count].value);
                cfg_node_id++;
                
            }
        }
        
        fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start);
        fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,end);
        
        cfg_node_list[cfg_node_id-2].parent_id=exp_start+1;
        cfg_node_list[cfg_node_id-2].left_side=1;
        cfg_node_list[cfg_node_id-1].parent_id=exp_start+1;
        
        
        if(strcmp(id_node_list[exp_start].type,id_node_list[end].type)==0){
            if(strcmp(op_node_list[exp_start+1].content,"=")==0 || strcmp(op_node_list[exp_start+1].content,"!=")==0 || strcmp(op_node_list[exp_start+1].content,">")==0 || strcmp(op_node_list[exp_start+1].content,"<")==0 || strcmp(op_node_list[exp_start+1].content,">=")==0 || strcmp(op_node_list[exp_start+1].content,"<=")==0 ){
                strcpy(op_node_list[exp_start+1].type,"BOOL");
            }
            else{
                strcpy(op_node_list[exp_start+1].type,id_node_list[end].type);}
            strcpy(op_node_list[exp_start+1].color,"white");
        }
        else{
            if(strcmp(op_node_list[exp_start+1].content,"=")==0 || strcmp(op_node_list[exp_start+1].content,"!=")==0 || strcmp(op_node_list[exp_start+1].content,">")==0 || strcmp(op_node_list[exp_start+1].content,"<")==0 || strcmp(op_node_list[exp_start+1].content,">=")==0 || strcmp(op_node_list[exp_start+1].content,"<=")==0 ){
                strcpy(op_node_list[exp_start+1].type,"BOOL");
            }
            else{
                strcpy(op_node_list[exp_start+1].type,id_node_list[end].type);}
                strcpy(op_node_list[exp_start+1].color,"red");
                sematic_error=1;
        }
        fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",exp_start+1,op_node_list[exp_start+1].content,op_node_list[exp_start+1].type,op_node_list[exp_start+1].color);
        
        cfg_node_list[cfg_node_id].id=exp_start+1;
        strcpy(cfg_node_list[cfg_node_id].name,token_list[exp_start+1].name);
        strcpy(cfg_node_list[cfg_node_id].value,token_list[exp_start+1].value);
        cfg_node_list[cfg_node_id].parent_id=parent_node_number;
        cfg_node_id++;
        
        
        return_exp.number=exp_start+1;
        strcpy(return_exp.type,op_node_list[exp_start+1].type);
        return (return_exp);
    }
    else if(op_number==2){
        
        
        start=exp_start;
        end=exp_end;
        
        
        base_line=cfg_node_id;
        //printf("%s",op_node_list[start+1].content);
        for(count=start;count<=end;count++){
            if(id_node_list[count].content[0]!='\0'){
                fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",count,id_node_list[count].content,id_node_list[count].type,id_node_list[count].color);
                cfg_node_list[cfg_node_id].id=count;
                strcpy(cfg_node_list[cfg_node_id].name,token_list[count].name);
                strcpy(cfg_node_list[cfg_node_id].value,token_list[count].value);
                cfg_node_id++;
                
            }
        }
        for(count=start;count<=end;count++){
            if(op_node_list[count].content[0]!='\0'){
                fprintf(paseroutput,"  n%d [label=\"%s:%s\",shape=box] \n",count,op_node_list[count].content,op_node_list[count].type);
                cfg_node_list[cfg_node_id].id=count;
                strcpy(cfg_node_list[cfg_node_id].name,token_list[count].name);
                strcpy(cfg_node_list[cfg_node_id].value,token_list[count].value);
                cfg_node_id++;
                
            }
        }
        
        
        
        if(strcmp(token_list[start+1].name,"COMPARE")==0){
            strcpy(op_node_list[exp_start+1].type,"BOOL");
            
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start+3);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+2);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+4);
            
            cfg_node_list[base_line].parent_id=exp_start+1;
            cfg_node_list[base_line].left_side=1;
            cfg_node_list[base_line+1].parent_id=exp_start+3;
            cfg_node_list[base_line+1].left_side=1;
            cfg_node_list[base_line+2].parent_id=exp_start+3;
            cfg_node_list[base_line+3].parent_id=parent_node_number;
            cfg_node_list[base_line+4].parent_id=exp_start+1;
            
            if(strcmp(id_node_list[exp_start+2].type,id_node_list[exp_start+4].type)==0){
                strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                strcpy(op_node_list[exp_start+3].color,"white");
                if(strcmp(id_node_list[exp_start].type,op_node_list[exp_start+3].type)==0){
                    strcpy(op_node_list[exp_start+1].type,op_node_list[exp_start+3].type);
                    strcpy(op_node_list[exp_start+1].color,"white");
                }
                else{
                    strcpy(op_node_list[exp_start+1].type,op_node_list[exp_start+3].type);
                    strcpy(op_node_list[exp_start+1].color,"red");
                    sematic_error=1;
                }
            }
            else{
                strcpy(op_node_list[exp_start+3].color,"red");
                strcpy(op_node_list[exp_start+1].color,"red");
                sematic_error=1;
            }
            
            return_exp.number=exp_start+1;
            strcpy(return_exp.type,op_node_list[exp_start+1].type);
            
        }
        
        else if(strcmp(token_list[start+3].name,"COMPARE")==0){
            strcpy(op_node_list[exp_start+3].type,"BOOL");
            
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start+2);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+1);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+4);
            
            cfg_node_list[base_line].parent_id=exp_start+1;
            cfg_node_list[base_line].left_side=1;
            cfg_node_list[base_line+1].parent_id=exp_start+1;
            cfg_node_list[base_line+2].parent_id=exp_start+3;
            cfg_node_list[base_line+3].parent_id=exp_start+3;
            cfg_node_list[base_line+3].left_side=1;
            cfg_node_list[base_line+4].parent_id=parent_node_number;
            
            if(strcmp(id_node_list[exp_start].type,id_node_list[exp_start+2].type)==0){
                
                strcpy(op_node_list[exp_start+1].type,id_node_list[exp_start+2].type);
                strcpy(op_node_list[exp_start+1].color,"white");
                
                if(strcmp(op_node_list[exp_start+1].type,id_node_list[exp_start+4].type)==0){
                    strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                    strcpy(op_node_list[exp_start+3].color,"white");
                }
                else{
                    strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                    strcpy(op_node_list[exp_start+3].color,"red");
                    sematic_error=1;
                }
            }
            else{
                strcpy(op_node_list[exp_start+1].color,"red");
                strcpy(op_node_list[exp_start+3].color,"red");
                sematic_error=1;
            }
            
            return_exp.number=exp_start+3;
            strcpy(return_exp.type,op_node_list[exp_start+3].type);
            
        }
        
        
        else if(strcmp(token_list[start+1].name,"MULTIPLICATIVE")==0){
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start+2);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+1);
            fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+4);
            
            cfg_node_list[base_line].parent_id=exp_start+1;
            cfg_node_list[base_line].left_side=1;
            cfg_node_list[base_line+1].parent_id=exp_start+1;
            cfg_node_list[base_line+2].parent_id=exp_start+3;
            cfg_node_list[base_line+3].parent_id=exp_start+3;
            cfg_node_list[base_line+3].left_side=1;
            cfg_node_list[base_line+4].parent_id=parent_node_number;
            
            if(strcmp(id_node_list[exp_start].type,id_node_list[exp_start+2].type)==0){
                strcpy(op_node_list[exp_start+1].type,id_node_list[exp_start+2].type);
                strcpy(op_node_list[exp_start+1].color,"white");
                if(strcmp(op_node_list[exp_start+1].type,id_node_list[exp_start+4].type)==0){
                    strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                    strcpy(op_node_list[exp_start+3].color,"white");
                }
                else{
                    strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                    strcpy(op_node_list[exp_start+3].color,"red");
                    sematic_error=1;
                }
            }
            else{
                strcpy(op_node_list[exp_start+1].color,"red");
                strcpy(op_node_list[exp_start+3].color,"red");
                sematic_error=1;
            }
            
            return_exp.number=exp_start+1;
            strcpy(return_exp.type,op_node_list[exp_start+1].type);
            
        }
        
        else if(strcmp(token_list[start+1].name,"ADDITIVE")==0){
            if (strcmp(token_list[start+3].name,"MULTIPLICATIVE")==0){
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start);
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start+3);
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+2);
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+4);
                
                cfg_node_list[base_line].parent_id=exp_start+1;
                cfg_node_list[base_line].left_side=1;
                cfg_node_list[base_line+1].parent_id=exp_start+3;
                cfg_node_list[base_line+1].left_side=1;
                cfg_node_list[base_line+2].parent_id=exp_start+3;
                cfg_node_list[base_line+3].parent_id=parent_node_number;
                cfg_node_list[base_line+4].parent_id=exp_start+1;
                
                if(strcmp(id_node_list[exp_start+2].type,id_node_list[exp_start+4].type)==0){
                    strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                    strcpy(op_node_list[exp_start+3].color,"white");
                    if(strcmp(id_node_list[exp_start].type,op_node_list[exp_start+3].type)==0){
                        strcpy(op_node_list[exp_start+1].type,op_node_list[exp_start+3].type);
                        strcpy(op_node_list[exp_start+1].color,"white");
                    }
                    else{
                        strcpy(op_node_list[exp_start+1].type,op_node_list[exp_start+3].type);
                        strcpy(op_node_list[exp_start+1].color,"red");
                        sematic_error=1;
                    }
                }
                else{
                    strcpy(op_node_list[exp_start+3].color,"red");
                    strcpy(op_node_list[exp_start+1].color,"red");
                    sematic_error=1;
                }
                
                return_exp.number=exp_start+1;
                strcpy(return_exp.type,op_node_list[exp_start+1].type);
                
            }
            else{
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start);
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+1,exp_start+2);
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+1);
                fprintf(paseroutput,"  n%d -> n%d \n", exp_start+3,exp_start+4);
                
                cfg_node_list[base_line].parent_id=exp_start+1;
                cfg_node_list[base_line].left_side=1;
                cfg_node_list[base_line+1].parent_id=exp_start+1;
                cfg_node_list[base_line+2].parent_id=exp_start+3;
                cfg_node_list[base_line+3].parent_id=exp_start+3;
                cfg_node_list[base_line+3].left_side=1;
                cfg_node_list[base_line+4].parent_id=parent_node_number;
                
                if(strcmp(id_node_list[exp_start].type,id_node_list[exp_start+2].type)==0){
                    strcpy(op_node_list[exp_start+1].type,id_node_list[exp_start+2].type);
                    strcpy(op_node_list[exp_start+1].color,"white");
                    if(strcmp(op_node_list[exp_start+1].type,id_node_list[exp_start+4].type)==0){
                        strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                        strcpy(op_node_list[exp_start+3].color,"white");
                    }
                    else{
                        strcpy(op_node_list[exp_start+3].type,id_node_list[exp_start+4].type);
                        strcpy(op_node_list[exp_start+3].color,"red");
                        sematic_error=1;
                    }
                }
                else{
                    strcpy(op_node_list[exp_start+1].color,"red");
                    strcpy(op_node_list[exp_start+3].color,"red");
                    sematic_error=1;
                }
                return_exp.number=exp_start+3;
                strcpy(return_exp.type,op_node_list[exp_start+3].type);
                
            }
            
        }
        
        
        
        
        return return_exp;
    }
    else{
        return_exp=exp_handler(exp_start,exp_end);
        return return_exp;
    }
    
    
foroptimization: ;
    
}





//=================================paser_assign=========
struct return_node paser_assign(int ass_start, int ass_end, int parent_node_number){
    int start,end,top_node_number;
    start=ass_start;
    end=ass_end;
    //printf("%d,%d",start,end);
    struct return_node return_ass;
    struct return_node exp_back;
    
    int count1=0;
    strcpy(id_node_list[start].color,"red");
    strcpy(id_node_list[start].content,token_list[start].value);
    for (count1=0;count1<g_viarable_id;count1++){
        if(strcmp(id_node_list[start].content,g_viarable_list[count1].name)==0){
            strcpy(id_node_list[start].color,"white");
            strcpy(id_node_list[start].type,g_viarable_list[count1].viatype);
        }
    }
    strcpy(op_node_list[start+1].content,":=");
    fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",start,id_node_list[start].content,id_node_list[start].type,id_node_list[start].color);
    fprintf(paseroutput,"  n%d -> n%d \n", start+1,start);
    
    cfg_node_list[cfg_node_id].id=start;
    strcpy(cfg_node_list[cfg_node_id].name,token_list[start].name);
    strcpy(cfg_node_list[cfg_node_id].value,token_list[start].value);
    cfg_node_list[cfg_node_id].parent_id=start+1;
    cfg_node_list[cfg_node_id].left_side=1;
    cfg_node_id++;
    
    
    if(strcmp(token_list[start+2].name,"READINT")==0){
        //printf("breakinreadint\n");
        strcpy(id_node_list[end].content,"readint");
        strcpy(id_node_list[end].type,"INT");
        strcpy(id_node_list[end].color,"white");
        fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",end,id_node_list[end].content,id_node_list[end].type,id_node_list[end].color);
        
        cfg_node_list[cfg_node_id].id=end;
        strcpy(cfg_node_list[cfg_node_id].name,id_node_list[end].content);
        cfg_node_list[cfg_node_id].parent_id=start+1;
        cfg_node_list[cfg_node_id].left_side=0;
        cfg_node_id++;
        
        if(strcmp(id_node_list[start].type,id_node_list[end].type)==0){
            strcpy(op_node_list[start+1].type,id_node_list[end].type);
            strcpy(op_node_list[start+1].color,"white");
        }
        else{
            strcpy(op_node_list[start+1].type,id_node_list[end].type);
            strcpy(op_node_list[start+1].color,"red");
            sematic_error=1;
        }
        
        fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",start+1,op_node_list[start+1].content,op_node_list[start+1].type,op_node_list[start+1].color);
        //fprintf(paseroutput,"  n%d -> n%d \n", start+1,start);
        fprintf(paseroutput,"  n%d -> n%d \n", start+1,end);
        
    }

    else{
        //printf("Enter assign!\n");
        
        exp_back=paser_expression(start+2,end,start+1);
        //printf("assign in last: %d,%s\n",exp_back.number,exp_back.type);
        //printf("parent type %d: %s\n",start, id_node_list[start].type);
        fprintf(paseroutput,"  n%d -> n%d \n",start+1, exp_back.number);

        
        if (strcmp(exp_back.type,id_node_list[start].type)==0){
            strcpy(op_node_list[start+1].type,exp_back.type);
            strcpy(op_node_list[start+1].color,"white");
        }
        else{
            strcpy(op_node_list[start+1].type,exp_back.type);
            strcpy(op_node_list[start+1].color,"red");
            sematic_error=1;
        }
        
    }
    
    fprintf(paseroutput,"  n%d [label=\"%s:%s\",fillcolor=\"%s\",shape=box] \n",start+1,op_node_list[start+1].content,op_node_list[start+1].type,op_node_list[start+1].color);
    
    cfg_node_list[cfg_node_id].id=start+1;
    strcpy(cfg_node_list[cfg_node_id].name,":=");
    //printf("parent_node_number :%d \n",parent_node_number);
    cfg_node_list[cfg_node_id].parent_id=parent_node_number;
    //make sure only one number returned.
    int judge = 0;
    int judge2 = 0;
    int number_id = 0;
    int temp =0;
    int k,h;
    for(k=0;k<cfg_node_id;k++){
        if(cfg_node_list[k].parent_id==start+1){
            if(strcmp(cfg_node_list[k].name,"num")==0){
                judge =1;
                number_id=k;
                break;
            }
        
        }
    }
    
    if(judge==1){
        for(h=0;h<c_pro_id;h++){
            if(strcmp(cfg_node_list[start].value,c_pro_list[h].var_name)==0){
                judge2=1;
                temp=h;
            }
        }
        if(judge2==0){
            strcpy(c_pro_list[c_pro_id].var_name,token_list[start].value);
            c_pro_list[c_pro_id].value=chartoint(cfg_node_list[number_id].value);
            c_pro_id++;
        }
        else{
            c_pro_list[temp].value=chartoint(cfg_node_list[number_id].value);
        }
    }
        
        
    cfg_node_id++;
    
    
    
    
    
    
    return_ass.number=ass_start+1;
    strcpy(return_ass.type,op_node_list[start+1].type);
    
    return return_ass;

}

struct return_node paser_state(int state_start, int state_end, int parent_node_number){
    int start_point, end_point,pivor,conductor_state,current_line;
    struct return_node top_node_return,top_node_value;
    
    pivor=state_start;
    start_point=state_start;
    end_point=state_end;
    node_number++;
    int temp,end_of_exp,while_node_number;
    int state_start_position;
    int countwhileif,countend;
    int counter;
    int noelse=0;
    int if_else_position;
    int if_end_position;
    int condition=0;
    int if_then_end_positon,else_position;
    
    do{
        
        
        if(strcmp(token_list[pivor].name,"ident")==0){
            
            if(strcmp(token_list[pivor+1].name,"ASGN")==0){
                
                
                conductor_state=pivor+2;
                current_line=token_list[pivor].line;
                
                
                while(strcmp(token_list[conductor_state].name,"SC")!=0){
                    //printf("Breakin state handler!\n");
                    
                    if(token_list[conductor_state].line>current_line){
                        printf("SC missed, please check line %d. \n", token_list[pivor].line);
                        top_node_return.number=-1;
                        goto state_end_state;
                    }
                    
                    else if(strcmp(token_list[conductor_state].name,"ident")==0 || strcmp(token_list[conductor_state].name,"boollit")==0 ||
                            strcmp(token_list[conductor_state].name,"num")==0||
                            strcmp(token_list[conductor_state].name,"LP")==0 ||
                            strcmp(token_list[conductor_state].name,"RP")==0 ||
                            strcmp(token_list[conductor_state].name,"COMPARE")==0 ||
                            strcmp(token_list[conductor_state].name,"ADDITIVE")==0 ||
                            strcmp(token_list[conductor_state].name,"MULTIPLICATIVE")==0 ||
                            strcmp(token_list[conductor_state].name,"READINT")==0){
                        conductor_state++;
                        
                    }
                    else{
                        printf("Wrong expression in state assign, please check line %d. \n", token_list[paserpointer].line);
                        top_node_return.number=-1;
                        goto state_end_state;
                        
                    }
                }
                
                //printf("%d , %d\n",paserpointer,conductor-1);
                top_node_value=paser_assign(pivor,conductor_state-1,parent_node_number);
                //printf("%d\n",top_node_number);
                if(top_node_value.number==-1){
                    top_node_return.number=-1;
                    goto state_end_state;
                }
                fprintf(paseroutput,"  n%d -> n%d \n",parent_node_number, top_node_value.number);
                
                pivor=conductor_state;
                
                
            }
            else{
                printf("Wrong asign statement in state, please check line %d. \n", token_list[pivor].line);
                //top_node_return.number=-1;
                //goto state_end_state;
            }
            
        
        }
        
        else if(strcmp(token_list[pivor].name,"WHILE")==0){
            countwhileif=1;
            countend=0;
            counter=pivor+1;
            while (countwhileif>0 ){
                if(strcmp(token_list[counter].name,"WHILE")==0 || strcmp(token_list[counter].name,"IF")==0){
                    countwhileif++;
                }
                if (strcmp(token_list[counter].name,"END")==0){
                    countwhileif--;
                }
                counter++;
            }
            
            temp=pivor;
            
            while (strcmp(token_list[temp].name,"DO")!=0){
                state_start_position++;
                temp++;
            }
            
            end_of_exp=temp-1;
            state_start_position=temp+1;
            //printf("%s\n",token_list[state_start_position].name);
            //printf("conductor:%d, paserpointer:%d in While\n",conductor,paserpointer);
            //printf("%s",token_list[conductor].name);
            
            //=========end of determin================
            
            //============start to handle expression===
            fprintf(paseroutput,"  n%d [label=\"while\",shape=box] \n", pivor);
            fprintf(paseroutput,"  n%d -> n%d \n",parent_node_number, pivor);
            
            cfg_node_list[cfg_node_id].id=pivor;
            strcpy(cfg_node_list[cfg_node_id].name,"while");
            cfg_node_list[cfg_node_id].parent_id=parent_node_number;
            cfg_node_id++;
            
            top_node_value=paser_expression(pivor+1,end_of_exp,pivor);
            
            fprintf(paseroutput,"  n%d -> n%d \n", pivor,top_node_value.number);
            while_node_number=pivor;
            
            node_number++;
            //============start to handle state========
            fprintf(paseroutput,"  n%d [label=\"stmt list\",shape=box] \n",temp);
            fprintf(paseroutput,"  n%d -> n%d \n",pivor,temp);
            
            cfg_node_list[cfg_node_id].id=temp;
            strcpy(cfg_node_list[cfg_node_id].name,"stmt");
            cfg_node_list[cfg_node_id].parent_id=temp;
            cfg_node_id++;
            
            top_node_value=paser_state(state_start_position,counter-1,temp);
            
            if(top_node_value.number==-1){
                top_node_return.number=-1;
                goto state_end_state;
            }
            
            node_number++;
            pivor=counter;
        }
        
        else if(strcmp(token_list[pivor].name,"IF")==0){
            countwhileif=1;
            countend=0;
            counter=pivor+1;
            while (countwhileif>0 ){
                if(strcmp(token_list[counter].name,"WHILE")==0 || strcmp(token_list[counter].name,"IF")==0){
                    countwhileif++;
                }
                if (strcmp(token_list[counter].name,"END")==0){
                    countwhileif--;
                }
                counter++;
            }
            
            temp=pivor;
            
            while (strcmp(token_list[temp].name,"THEN")!=0){
                state_start_position++;
                temp++;
            }
            
            end_of_exp=temp-1;
            int if_then_position = temp+1;
            
            while (temp<counter-1){
                //printf("%d\n",temp);
                if (strcmp(token_list[temp].name,"ELSE")==0) {
                    if (condition==0) {
                        break;
                    }
                }
                if (strcmp(token_list[temp].name,"WHILE")==0 || strcmp(token_list[temp].name,"IF")==0) {
                    condition++;
                }
                if (strcmp(token_list[temp].name,"END")==0 ) {
                    condition--;
                }
                temp++;
            }
            
             if_then_end_positon=temp-1;
             else_position=temp;
            
            //printf("else positon: %d",else_position);
            
            if (temp<counter-2) {
                if_else_position=temp+1;
                if_end_position=counter-2;
                
            }
            else{
                noelse=1;
            }
            
            fprintf(paseroutput,"  n%d [label=\"if\",shape=box] \n", pivor);
            fprintf(paseroutput,"  n%d -> n%d \n",parent_node_number, pivor);
            
            cfg_node_list[cfg_node_id].id=pivor;
            strcpy(cfg_node_list[cfg_node_id].name,"if");
            cfg_node_list[cfg_node_id].parent_id=parent_node_number;
            cfg_node_id++;
            
            top_node_value=paser_expression(pivor+1,end_of_exp,pivor);
            
            fprintf(paseroutput,"  n%d -> n%d \n", pivor,top_node_value.number);
            
            
            //============start to handle state========
            fprintf(paseroutput,"  n%d [label=\"then\",shape=box] \n",if_then_position-1);
            fprintf(paseroutput,"  n%d -> n%d \n",pivor,if_then_position-1);
            
            cfg_node_list[cfg_node_id].id=if_then_position-1;
            strcpy(cfg_node_list[cfg_node_id].name,"then");
            cfg_node_list[cfg_node_id].parent_id=pivor;
            cfg_node_id++;
            
            //printf("%d, %s",state_end_position,token_list[state_end_position].name);
            top_node_value=paser_state(if_then_position,if_then_end_positon,if_then_position-1);
            
            if (top_node_value.number==-1) {
                top_node_return.number=-1;
                goto state_end_state;
            }
            
            
            
            //printf("else position:%d, end position:%d\n",if_else_position,if_end_position);
            
            if (noelse==0) {
                //printf("else in state postion: %d,%s \n",else_position,token_list[else_position].name);
                fprintf(paseroutput,"  n%d [label=\"else\",shape=box] \n",else_position);
                fprintf(paseroutput,"  n%d -> n%d \n",pivor,else_position);
                
                cfg_node_list[cfg_node_id].id=else_position;
                strcpy(cfg_node_list[cfg_node_id].name,"else");
                cfg_node_list[cfg_node_id].parent_id=pivor;
                cfg_node_id++;
                
                //printf("%d, %s",state_end_position,token_list[state_end_position].name);
                top_node_value=paser_state(else_position+1,if_end_position,else_position);
                
                if (top_node_value.number==-1) {
                    top_node_return.number=-1;
                    goto state_end_state;
                }
                
                
            }
            
            
            pivor=counter;
            
            
        }
        
        
        //============================================handle writeint=================
        else if(strcmp(token_list[pivor].name,"WRITEINT")==0){
            
            conductor_state=pivor+1;
            current_line=token_list[pivor].line;
            
            
            while(strcmp(token_list[conductor_state].name,"SC")!=0){
                //printf("%d,%d",current_line,token_list[conductor].line);
                if(token_list[conductor_state].line>current_line){
                    printf("SC missed, please check line %d. \n", token_list[pivor].line);
                    top_node_return.number=-1;
                    goto state_end_state;
                }
                
                if(strcmp(token_list[conductor_state].name,"ident")==0 || strcmp(token_list[conductor_state].name,"boollit")==0 ||
                   strcmp(token_list[conductor_state].name,"num")==0||
                   strcmp(token_list[conductor_state].name,"LP")==0 ||
                   strcmp(token_list[conductor_state].name,"RP")==0 ||
                   strcmp(token_list[conductor_state].name,"COMPARE")==0 ||
                   strcmp(token_list[conductor_state].name,"ADDITIVE")==0 ||
                   strcmp(token_list[conductor_state].name,"MULTIPLICATIVE")==0){
                    conductor_state++;
                    
                }
                else{
                    printf("Wrong expression in state writeint, please check line %d. \n", token_list[pivor].line);
                    top_node_return.number=-1;
                    goto state_end_state;
                    
                }
                
                
                
            }
            
            
            
            
            
            top_node_value=paser_expression(pivor+1,conductor_state-1,pivor);
            
            if(top_node_value.number==-1){
                top_node_return.number=-1;
                goto state_end_state;
            }
            
            if(strcmp(top_node_value.type,"INT")!=0){
                fprintf(paseroutput,"  n%d [label=\"writeint\",fillcolor=\"red\"shape=box] \n", pivor);
            }
            else{
                fprintf(paseroutput,"  n%d [label=\"writeint\",shape=box] \n", pivor);}
            fprintf(paseroutput,"  n%d -> n%d \n",parent_node_number, pivor);
            fprintf(paseroutput,"  n%d -> n%d \n", pivor,top_node_value.number);
            
            cfg_node_list[cfg_node_id].id=pivor;
            strcpy(cfg_node_list[cfg_node_id].name,"writeint");
            cfg_node_list[cfg_node_id].parent_id=parent_node_number;
            cfg_node_id++;
            
            pivor=conductor_state;
            
            
        }
        
        
    
        
        
        pivor++;
    }while(pivor<end_point);
    
  state_end_state: return top_node_return;
}








void paserscanner(){
    //printf("Output tokenid : %d \n", tokenid);
    
    //printf("Output first toke list: Name: %s \n", token_list[paserpointer].name);
    int conductor, current_line;
    int last_end;
    int top_node_number;
    int count1;
    int count_while_if = 0;
    int count_end = 0;
    int temp, state_end_position,state_start_position,end_of_exp,if_exp_start,if_then_position,if_then_end_positon,if_else_position,if_end_position,noelse;
    int while_node_number,if_node_number;
    int condition =0;
    noelse=0;
    last_end=tokenid-1;
    struct return_node top_node_value;
    //printf("Output last toke list: Name: %s \n", token_list[last_end].name);
    
    do{
        //printf("paserpointer: %d,%s\n", paserpointer,token_list[paserpointer].name);
        
        if (paserpointer==0){
            if (strcmp(token_list[paserpointer].name,"PROGRAM")==0){
                fprintf(paseroutput,"digraph AST_file { \n");
                fprintf(paseroutput,"  ordering=out; \n");
                fprintf(paseroutput,"  node [shape = box, style = filled, fillcolor=\"white\"]; \n");
                fprintf(paseroutput,"  n1 [label=\"program\",shape=box] \n");
                fprintf(paseroutput,"  n2 [label=\"decl list\",shape=box] \n");
                fprintf(paseroutput,"  n1 -> n2 \n");
                
                cfg_node_list[cfg_node_id].id=1;
                strcpy(cfg_node_list[cfg_node_id].name,"program");
                cfg_node_id++;
                cfg_node_list[cfg_node_id].id=2;
                strcpy(cfg_node_list[cfg_node_id].name,"decl");
                cfg_node_list[cfg_node_id].parent_id=1;
                cfg_node_id++;
                
            }
            else{
                printf("Key word: program missed, please check line %d. \n", token_list[paserpointer].line);
                goto finalstate;
            }
            
        }
        
        else if(paserpointer == last_end){
            //printf("Detect final End!\n");
            if (strcmp(token_list[paserpointer].name,"END")==0){
                fprintf(paseroutput,"} \n");}
            else{
                printf("Key word : end missed, please check line %d. \n", token_list[paserpointer].line);
                goto finalstate;
            }
        }
        
        else if (strcmp(token_list[paserpointer].name,"BEGIN")==0){
            fprintf(paseroutput,"  n3 [label=\"stmt list\",shape=box] \n");
            fprintf(paseroutput,"  n1 -> n3 \n");
            cfg_node_list[cfg_node_id].id=3;
            strcpy(cfg_node_list[cfg_node_id].name,"stmt");
            cfg_node_list[cfg_node_id].parent_id=1;
            cfg_node_id++;
            //printf("test_end_begine\n");
        }
        
        else {
            if (strcmp(token_list[paserpointer].name,"VAR")==0){
                if (strcmp(token_list[paserpointer+1].name, "ident")==0) {
                    if (strcmp(token_list[paserpointer+2].name, "AS")==0) {
                        if (strcmp(token_list[paserpointer+4].name, "SC")==0) {
                            
                        
                        if (strcmp(token_list[paserpointer+3].name, "INT")==0 || strcmp(token_list[paserpointer+3].name, "BOOL")==0) {
                            fprintf(paseroutput,"  n%d [label=\"decl:'%s':%s\",shape=box] \n", node_number,token_list[paserpointer+1].value,token_list[paserpointer+3].name);
                            fprintf(paseroutput,"  n2 -> n%d \n", node_number);
                            strcpy(g_viarable_list[g_viarable_id].name,token_list[paserpointer+1].value);
                            strcpy(g_viarable_list[g_viarable_id].viatype,token_list[paserpointer+3].name);
                            
                            cfg_node_list[cfg_node_id].id=node_number;
                            strcpy(cfg_node_list[cfg_node_id].name,token_list[paserpointer+1].value);
                            strcpy(cfg_node_list[cfg_node_id].value,token_list[paserpointer+3].name);
                            cfg_node_list[cfg_node_id].parent_id=2;
                            cfg_node_id++;
                            
                            
                            g_viarable_id++;
                            paserpointer=paserpointer+4;
                            node_number++;
                                     }
                            else{printf("Wrong viarable type is detected, please check line %d. \n", token_list[paserpointer].line);
                                goto finalstate;}
                            
                            }
                            else{
                                printf("SC missed, please check line %d. \n", token_list[paserpointer].line);
                                goto finalstate;
                            }
                    }
                }
            }
            

            else if(strcmp(token_list[paserpointer].name,"ident")==0){

                if(strcmp(token_list[paserpointer+1].name,"ASGN")==0){
                    

                    conductor=paserpointer+2;
                    current_line=token_list[paserpointer].line;
                    
                    //printf("test_breakinident\n");
                    while(strcmp(token_list[conductor].name,"SC")!=0){
                        //printf("%d,%s",conductor,token_list[conductor].name);
                        if(token_list[conductor].line>current_line){
                            printf("SC missed, please check line %d. \n", token_list[paserpointer].line);
                            goto finalstate;
                        }
                        
                        else if(strcmp(token_list[conductor].name,"ident")==0 || strcmp(token_list[conductor].name,"boollit")==0 ||
                           strcmp(token_list[conductor].name,"num")==0||
                           strcmp(token_list[conductor].name,"LP")==0 ||
                           strcmp(token_list[conductor].name,"RP")==0 ||
                           strcmp(token_list[conductor].name,"COMPARE")==0 ||
                           strcmp(token_list[conductor].name,"ADDITIVE")==0 ||
                           strcmp(token_list[conductor].name,"MULTIPLICATIVE")==0 ||
                           strcmp(token_list[conductor].name,"READINT")==0){
                            conductor++;
                            
                        }
                        else{
                            printf("Wrong expression in assign, please check line %d. \n", token_list[paserpointer].line);
                            goto finalstate;
                            
                        }
                    }
                    
                    //printf("%d , %d\n",paserpointer,conductor-1);
                    top_node_value=paser_assign(paserpointer,conductor-1,3);
                    //printf("%d\n",top_node_number);
                    if(top_node_value.number==-1){
                        goto finalstate;
                    }
                    fprintf(paseroutput,"  n3 -> n%d \n", top_node_value.number);
                    
                    paserpointer=conductor;
                    
                    
                }
                else{
                    printf("Wrong asign statement, please check line %d. \n", token_list[paserpointer].line);
                    //goto finalstate;    //mark for test temporary **********
                }
                
            }
            
            //Handle while
            else if (strcmp(token_list[paserpointer].name,"WHILE")==0){
                
                //============determine the while loop was bounded correctly=================
                count_while_if=1;
                count_end=0;
                temp=0;
                conductor=paserpointer+1;
                while (count_while_if>0 ){
                    if(strcmp(token_list[conductor].name,"WHILE")==0 || strcmp(token_list[conductor].name,"IF")==0){
                        count_while_if++;
                    }
                    if (strcmp(token_list[conductor].name,"END")==0) {
                        count_while_if--;
                    }
                    conductor++;
                }
                
                temp=count_while_if;

                
                state_end_position=conductor-2;
                state_start_position=paserpointer+1;
                
                temp=paserpointer+1;
                //===determin the end position====
                while (strcmp(token_list[temp].name,"DO")!=0){
                        state_start_position++;
                    temp++;
                }
                //printf("%s\n",token_list[state_start_position].name);
                //printf("%s\n",token_list[state_end_position].name);
                end_of_exp=state_start_position-1;
                state_start_position++;
                //printf("%s\n",token_list[state_start_position].name);
                //printf("conductor:%d, paserpointer:%d in While\n",conductor,paserpointer);
                //printf("%s",token_list[conductor].name);
                
                //=========end of determin================
                
                //============start to handle expression===
                fprintf(paseroutput,"  n%d [label=\"while\",shape=box] \n", paserpointer);
                fprintf(paseroutput,"  n3 -> n%d \n", paserpointer);
                
                cfg_node_list[cfg_node_id].id=paserpointer;
                strcpy(cfg_node_list[cfg_node_id].name,"while");
                cfg_node_list[cfg_node_id].parent_id=3;
                cfg_node_id++;
                
                top_node_value=paser_expression(paserpointer+1,end_of_exp,paserpointer);
                
                fprintf(paseroutput,"  n%d -> n%d \n", paserpointer,top_node_value.number);
                
                
                //node_number++;
                //============start to handle state========
                fprintf(paseroutput,"  n%d [label=\"stmt list\",shape=box] \n",temp);
                fprintf(paseroutput,"  n%d -> n%d \n",paserpointer,temp);
                
                cfg_node_list[cfg_node_id].id=temp;
                strcpy(cfg_node_list[cfg_node_id].name,"stmt");
                cfg_node_list[cfg_node_id].parent_id=paserpointer;
                cfg_node_id++;
                
                //printf("%d, %s",state_end_position,token_list[state_end_position].name);
                top_node_value=paser_state(state_start_position,state_end_position,temp);
                
                if (top_node_value.number==-1) {
                    goto finalstate;
                }
                
                //node_number++;

                paserpointer=conductor;
                
                    
                    }
            
            
            //Handle if
            else if (strcmp(token_list[paserpointer].name,"IF")==0){
                //============determine the while loop was bounded correctly=================
                count_while_if=1;
                count_end=0;
                temp=0;
                conductor=paserpointer+1;
                while (count_while_if>0 ){
                    if(strcmp(token_list[conductor].name,"WHILE")==0 || strcmp(token_list[conductor].name,"IF")==0){
                        count_while_if++;
                    }
                    if (strcmp(token_list[conductor].name,"END")==0) {
                        count_while_if--;
                    }
                    conductor++;
                }
                
                
                state_end_position=conductor-2;
                
                if_exp_start=paserpointer+1;
                
                temp=paserpointer+1;
                //===determin the end position====
                while (strcmp(token_list[temp].name,"THEN")!=0){
                    
                    temp++;
                }
                
                if_then_position=temp+1;
                //printf("%s\n",token_list[state_start_position].name);
                //printf("%s\n",token_list[state_end_position].name);
                end_of_exp=temp-1;
                
                while (temp<conductor-1){
                    if (strcmp(token_list[temp].name,"ELSE")==0) {
                        if (condition==0) {
                            
                            break;
                        }
                    }
                    if (strcmp(token_list[temp].name,"WHILE")==0 || strcmp(token_list[temp].name,"IF")==0) {
                        //printf ("Test in breadk\n");
                        condition++;
                    }
                    if (strcmp(token_list[temp].name,"END")==0 ) {
                        condition--;
                    }
                    temp++;
                }
                
                if_then_end_positon=temp-1;
                
                if (temp<conductor-2) {
                    if_else_position=temp+1;
                    if_end_position=conductor-2;
                    
                }
                else{
                    noelse=1;
                }
                
                fprintf(paseroutput,"  n%d [label=\"if\",shape=box] \n", paserpointer);
                fprintf(paseroutput,"  n3 -> n%d \n", paserpointer);
                
                cfg_node_list[cfg_node_id].id=paserpointer;
                strcpy(cfg_node_list[cfg_node_id].name,"if");
                cfg_node_list[cfg_node_id].parent_id=3;
                cfg_node_id++;
                
                top_node_value=paser_expression(paserpointer+1,end_of_exp,paserpointer);
                
                fprintf(paseroutput,"  n%d -> n%d \n", paserpointer,top_node_value.number);
                if_node_number=paserpointer;
                
                
                
                //============start to handle state========
                fprintf(paseroutput,"  n%d [label=\"then\",shape=box] \n",if_then_position-1);
                fprintf(paseroutput,"  n%d -> n%d \n",if_node_number,if_then_position-1);
                
                cfg_node_list[cfg_node_id].id=if_then_position-1;
                strcpy(cfg_node_list[cfg_node_id].name,"then");
                cfg_node_list[cfg_node_id].parent_id=if_node_number;
                cfg_node_id++;
                
                //printf("%d, %s",state_end_position,token_list[state_end_position].name);
                top_node_value=paser_state(if_then_position,if_then_end_positon,if_then_position-1);
                
                if (top_node_value.number==-1) {
                    goto finalstate;
                }
                
                //node_number++;
                
                //printf("else position:%d, end position:%d\n",if_else_position,if_end_position);
                
                if (noelse==0) {
                    //printf("else in main postion: %d,%s \n",temp,token_list[temp].name);
                    fprintf(paseroutput,"  n%d [label=\"else\",shape=box] \n",temp);
                    fprintf(paseroutput,"  n%d -> n%d \n",if_node_number,temp);
                    
                    cfg_node_list[cfg_node_id].id=temp;
                    strcpy(cfg_node_list[cfg_node_id].name,"else");
                    cfg_node_list[cfg_node_id].parent_id=if_node_number;
                    cfg_node_id++;
                    
                    //printf("%d, %s",state_end_position,token_list[state_end_position].name);
                    top_node_value=paser_state(if_else_position,if_end_position,temp);
                    
                    if (top_node_value.number==-1) {
                        goto finalstate;
                    }
                    
                    node_number++;
                }
                
                
                paserpointer=conductor;
                //printf("last point in main:%d,%s \n",paserpointer,token_list[paserpointer].name);
            
            }//===================end of if===============================
            
            
            
            //Handle writeint
            else if (strcmp(token_list[paserpointer].name,"WRITEINT")==0){
                conductor=paserpointer+1;
                current_line=token_list[paserpointer].line;
                
                
                while(strcmp(token_list[conductor].name,"SC")!=0){
                    //printf("%d,%d",current_line,token_list[conductor].line);
                    if(token_list[conductor].line>current_line){
                        printf("SC missed, please check line %d. \n", token_list[paserpointer].line);
                        goto finalstate;
                    }
                    
                    if(strcmp(token_list[conductor].name,"ident")==0 || strcmp(token_list[conductor].name,"boollit")==0 ||
                       strcmp(token_list[conductor].name,"num")==0||
                       strcmp(token_list[conductor].name,"LP")==0 ||
                       strcmp(token_list[conductor].name,"RP")==0 ||
                       strcmp(token_list[conductor].name,"COMPARE")==0 ||
                       strcmp(token_list[conductor].name,"ADDITIVE")==0 ||
                       strcmp(token_list[conductor].name,"MULTIPLICATIVE")==0){
                        conductor++;
                        
                    }
                    else{
                        printf("Wrong expression in if, please check line %d. \n", token_list[paserpointer].line);
                        goto finalstate;

                    }
                    
                    
                    
                }
                
                
                
                
                
                top_node_value=paser_expression(paserpointer+1,conductor-1,paserpointer);
                
                if(top_node_value.number==-1){
                    goto finalstate;
                }
                if(strcmp(top_node_value.type,"INT")!=0){
                    fprintf(paseroutput,"  n%d [label=\"writeint\",fillcolor=\"red\"shape=box] \n", paserpointer);
                    cfg_node_list[cfg_node_id].id=paserpointer;
                    strcpy(cfg_node_list[cfg_node_id].name,"writeint");
                    cfg_node_list[cfg_node_id].parent_id=3;
                    cfg_node_id++;
                    
                }
                else{
                    fprintf(paseroutput,"  n%d [label=\"writeint\",shape=box] \n", paserpointer);}
                fprintf(paseroutput,"  n3 -> n%d \n", paserpointer);
                fprintf(paseroutput,"  n%d -> n%d \n", paserpointer,top_node_value.number);
                
                cfg_node_list[cfg_node_id].id=paserpointer;
                strcpy(cfg_node_list[cfg_node_id].name,"writeint");
                cfg_node_list[cfg_node_id].parent_id=3;
                cfg_node_id++;
                
                paserpointer=conductor;
                //node_number++;
                
                }
            
            
 
        }
        

    paserpointer++;
        //printf("%d",paserpointer);
        
    }while (paserpointer<tokenid);
    printf("Paser finished successfully! AST Dot file could be reviewed in workdir! \n");
    
    
finalstate: ;
    
}


//====================handle to generate CFG=============================



int handle_exp(int id){
    int index;
    int r_child_index,l_child_index;
    int l_return,r_return;
    char l_char[20],r_char[20];
    int return_reg_id;
    char r_ass_l[30] = "r_";
    char r_ass_r[30] = "r_";
    char reg_prefix[30] = "r";
    l_child_index=get_l_index(id);
    r_child_index=get_r_index(id);
    
    if (strcmp(cfg_node_list[l_child_index].name,"ident")==0 || strcmp(cfg_node_list[l_child_index].name,"num")==0) {
        if (strcmp(cfg_node_list[l_child_index].name,"ident")==0) {
            
            strcat(r_ass_l,cfg_node_list[l_child_index].value);
            strcpy(l_char,r_ass_l);
        }
        else{
            strcpy(reg_prefix,"r");
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"loadI");
            strcpy(t_code_list[t_code_id].operand1,cfg_node_list[l_child_index].value);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            t_code_list[t_code_id].dest1=t_reg_id;
            strcpy(l_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
    }
    else{
        strcpy(reg_prefix,"r");
        l_return=handle_exp(cfg_node_list[l_child_index].id);
        inttoreg_id(l_return);
        strcat(reg_prefix,reg_id);
        strcpy(l_char,reg_prefix);
        strcpy(reg_id,"\0");
        strcpy(r_ass_l,"r_");
        strcpy(r_ass_r,"r_");
        strcpy(reg_prefix,"r");
    }
    
    if (strcmp(cfg_node_list[r_child_index].name,"ident")==0 || strcmp(cfg_node_list[r_child_index].name,"num")==0) {
        if (strcmp(cfg_node_list[r_child_index].name,"ident")==0) {
            strcat(r_ass_r,cfg_node_list[r_child_index].value);
            strcpy(r_char,r_ass_r);
        }
        else{
            strcpy(reg_prefix,"r");
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"loadI");
            strcpy(t_code_list[t_code_id].operand1,cfg_node_list[r_child_index].value);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            t_code_list[t_code_id].dest1=t_reg_id;
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
    }
    else{
        strcpy(reg_prefix,"r");
        r_return=handle_exp(cfg_node_list[r_child_index].id);
        inttoreg_id(r_return);
        strcat(reg_prefix,reg_id);
        strcpy(r_char,reg_prefix);
        strcpy(reg_id,"\0");
        strcpy(r_ass_l,"r_");
        strcpy(r_ass_r,"r_");
        strcpy(reg_prefix,"r");
    }
    

    index=idtoindex(id);
    if (strcmp(cfg_node_list[index].name,"COMPARE")==0) {
        if (strcmp(cfg_node_list[index].value,"=")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"cmp_E");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            t_code_list[t_code_id].dest1=t_reg_id;
            strcpy(r_char,reg_prefix);
            //printf("%s, %s \n",t_code_list[t_code_id].operator,t_code_list[t_code_id].operand1);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else if (strcmp(cfg_node_list[index].value,"!=")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"cmp_NE");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else if (strcmp(cfg_node_list[index].value,"<")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"cmp_LS");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else if (strcmp(cfg_node_list[index].value,">")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"cmp_GT");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else if (strcmp(cfg_node_list[index].value,"<=")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"cmp_LE");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else{
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"cmp_GE");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
    }
    
    else if (strcmp(cfg_node_list[index].name,"ADDITIVE")==0) {
        if (strcmp(cfg_node_list[index].value,"+")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"add");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else{
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"sub");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
    }
    else if (strcmp(cfg_node_list[index].name,"MULTIPLICATIVE")==0){
     
        if (strcmp(cfg_node_list[index].value,"*")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"mult");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            //printf("%s, %s \n",t_code_list[t_code_id].operator,t_code_list[t_code_id].operand1);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else if (strcmp(cfg_node_list[index].value,"div")==0) {
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"div");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
        else{
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"mod");
            strcpy(t_code_list[t_code_id].operand1,l_char);
            strcpy(t_code_list[t_code_id].operand2,r_char);
            inttoreg_id(t_reg_id);
            strcat(reg_prefix,reg_id);
            strcpy(t_code_list[t_code_id].destination,reg_prefix);
            strcpy(r_char,reg_prefix);
            
            strcpy(reg_id,"\0");
            strcpy(r_ass_l,"r_");
            strcpy(r_ass_r,"r_");
            strcpy(reg_prefix,"r");
            t_reg_id++;
            t_code_id++;
        }
    }
    
    return t_reg_id-1;
}

int handle_state(int id){
    int r_child_index,l_child_index;
    int return_reg_id;
    char r_ass_l[30] = "r_";
    char r_ass_r[30] = "r_";
    char reg_prefix[30] = "r";
    int i,l,k;
    
    for (i=0; i<cfg_node_id; i++) {
        if (cfg_node_list[i].parent_id==id){
            if (strcmp(cfg_node_list[i].name,":=")==0) {    //handle assign
                
                r_child_index=get_r_index(cfg_node_list[i].id);
                l_child_index=get_l_index(cfg_node_list[i].id);
                strcat(r_ass_l,cfg_node_list[l_child_index].value);
                
                if (strcmp(cfg_node_list[r_child_index].name,"readint")==0) { //handle readint
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"readInt");
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    
                }
                
                else if(strcmp(cfg_node_list[r_child_index].name,"ident")==0){
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"i2i");
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    strcat(r_ass_r,cfg_node_list[r_child_index].value);
                    strcpy(t_code_list[t_code_id].operand1,r_ass_r);
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                
                else if(strcmp(cfg_node_list[r_child_index].name,"num")==0){
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"loadI");
                    strcpy(t_code_list[t_code_id].operand1,cfg_node_list[r_child_index].value);
                    inttoreg_id(t_reg_id);
                    strcat(reg_prefix,reg_id);
                    strcpy(t_code_list[t_code_id].destination,reg_prefix);
                    t_code_id++;
                    
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"i2i");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    t_reg_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                
                else if(strcmp(cfg_node_list[r_child_index].name,"boollit")==0){
                    if (strcmp(cfg_node_list[r_child_index].value,"true")==0) {
                        t_code_list[t_code_id].block_id = block_id;
                        strcpy(t_code_list[t_code_id].operator,"loadI");
                        strcpy(t_code_list[t_code_id].operand1,"1");
                        strcat(r_ass_r,cfg_node_list[l_child_index].value);
                        strcpy(t_code_list[t_code_id].destination,r_ass_r);
                        
                        t_code_id++;
                        strcpy(r_ass_l,"r_");
                        strcpy(r_ass_r,"r_");
                    }
                    else{
                        t_code_list[t_code_id].block_id = block_id;
                        strcpy(t_code_list[t_code_id].operator,"loadI");
                        strcpy(t_code_list[t_code_id].operand1,"0");
                        strcat(r_ass_r,cfg_node_list[l_child_index].value);
                        strcpy(t_code_list[t_code_id].destination,r_ass_r);
                        
                        t_code_id++;
                        strcpy(r_ass_l,"r_");
                        strcpy(r_ass_r,"r_");
                    }
                }
                
                else{
                    return_reg_id = handle_exp(cfg_node_list[r_child_index].id);
                    inttoreg_id(return_reg_id);
                    strcat(reg_prefix,reg_id);
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"i2i");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                    
                }
                
                
            }
            
            else if (strcmp(cfg_node_list[i].name,"while")==0) {
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+1);
                char B_pre[5]="B\0";
                strcat(B_pre,reg_id);
                strcpy(t_code_list[t_code_id].destination,B_pre);
                b_relation_list[relationid].parent=block_id;
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                t_code_id++;
                
                block_id++;
                
                int while_exp_index,while_stmt_index;     //2
                int while_b_id,old_t_id;
                int temp_t;
                
                for (l=0; l<cfg_node_id; l++) {
                    if (cfg_node_list[l].parent_id==cfg_node_list[i].id) {
                        if (strcmp(cfg_node_list[l].name,"stmt")==0) {
                            while_stmt_index=l;
                        }
                        else{
                            while_exp_index=l;
                        }
                    }
                }
                
                return_reg_id=handle_exp(cfg_node_list[while_exp_index].id);
                inttoreg_id(return_reg_id);
                t_code_list[t_code_id].block_id = block_id;
                temp_t=t_code_id;
                strcpy(t_code_list[t_code_id].operator,"cbr");
                strcat(reg_prefix,reg_id);
                strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                char dest1[5]="B\0";
                inttoreg_id(block_id+1);
                strcat(dest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,dest1);
                old_t_id=t_code_id;
                
                t_code_id++;
                strcpy(reg_prefix,"r");
                
                
                b_relation_list[relationid].parent=block_id;
                b_relation_list[relationid].child=block_id+1;    //2->3
                relationid++;
                
                
                while_b_id=block_id;                             //keep 2
                block_id++;                //3
                return_reg_id=handle_state(cfg_node_list[while_stmt_index].id);
                strcpy(dest1,"B\0");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(while_b_id);
                strcat(dest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,dest1);
                t_code_id++;
                b_relation_list[relationid].parent=block_id;  //go back while blcok
                b_relation_list[relationid].child=while_b_id;
                relationid++;
                
                block_id++;
                char dest2[5]="B\0";
                inttoreg_id(block_id);
                strcat(dest2,reg_id);
                strcpy(t_code_list[temp_t].destination2,dest2);
                
                b_relation_list[relationid].parent=while_b_id;  //2->last
                b_relation_list[relationid].child=block_id;
                relationid++;
            }
            
            else if (strcmp(cfg_node_list[i].name,"if")==0) {
                printf("test point\n");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+1);
                char C_pre[5]="B\0";
                strcat(C_pre,reg_id);
                strcpy(t_code_list[t_code_id].destination,C_pre);
                b_relation_list[relationid].parent=block_id;
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                t_code_id++;
                
                block_id++;
                
                int if_exp_index,if_then_index,if_else_index;
                
                for (l=0; l<cfg_node_id; l++) {
                    if (cfg_node_list[l].parent_id==cfg_node_list[i].id) {
                        if (strcmp(cfg_node_list[l].name,"then")==0) {
                            if_then_index=l;
                        }
                        else if (strcmp(cfg_node_list[l].name,"else")==0) {
                            if_else_index=l;
                        }
                        else{
                            if_exp_index=l;
                        }
                    }
                }
                
                int cbr_id,if_b_id, then_relation_id;    //5
                
                return_reg_id=handle_exp(cfg_node_list[if_exp_index].id); // 5
                inttoreg_id(return_reg_id);
                t_code_list[t_code_id].block_id = block_id;
                cbr_id=t_code_id;
                strcpy(t_code_list[t_code_id].operator,"cbr");
                strcat(reg_prefix,reg_id);
                strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                char idest1[5]="B\0";
                inttoreg_id(block_id+1);
                strcat(idest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,idest1);
                t_code_id++;
                
                strcpy(reg_prefix,"r");
                
                b_relation_list[relationid].parent=block_id;   //if to then 5->6
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                
                if_b_id=block_id;
                block_id++;
                b_relation_list[relationid].parent=block_id;  //6->
                then_relation_id=relationid;
                
                return_reg_id=handle_state(cfg_node_list[if_then_index].id);
                strcpy(idest1,"B\0");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+2);
                strcat(idest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,idest1);
                t_code_id++;
                block_id++;
                relationid++;
                
                b_relation_list[relationid].parent=if_b_id;
                b_relation_list[relationid].child=block_id;        //5->7
                relationid++;
                
                
                char idest2[5]="B\0";
                inttoreg_id(block_id);
                strcat(idest2,reg_id);
                strcpy(t_code_list[cbr_id].destination2,idest2);
                
                
                
                
                return_reg_id=handle_state(cfg_node_list[if_else_index].id);
                
                strcpy(idest1,"B\0");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+1);
                strcat(idest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,idest1);
                t_code_id++;
                b_relation_list[relationid].parent=block_id;   //7->8
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                b_relation_list[then_relation_id].child=block_id+1; //6->8
                block_id++;
            }
            
            else if (strcmp(cfg_node_list[i].name,"writeint")==0) {
                r_child_index=get_r_index(cfg_node_list[i].id);
                
                if (strcmp(cfg_node_list[r_child_index].name,"ident")==0) {
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"writeInt");
                    strcat(r_ass_r,cfg_node_list[r_child_index].value);
                    strcpy(t_code_list[t_code_id].operand1,r_ass_r);
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                else if (strcmp(cfg_node_list[r_child_index].name,"num")==0){
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"loadI");
                    strcpy(t_code_list[t_code_id].operand1,cfg_node_list[r_child_index].value);
                    inttoreg_id(t_reg_id);
                    strcat(reg_prefix,reg_id);
                    strcpy(t_code_list[t_code_id].destination,reg_prefix);
                    t_code_id++;
                    
                    
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"writeInt");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    t_reg_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                else{
                    return_reg_id = handle_exp(cfg_node_list[r_child_index].id);
                    inttoreg_id(return_reg_id);
                    strcat(reg_prefix,reg_id);
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"writeInt");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                
                
            }
        }
    }
    
    return t_reg_id-1;
}

void cfggen(){
    int r_child_index,l_child_index;
    int return_reg_id;
    char r_ass_l[30] = "r_";
    char r_ass_r[30] = "r_";
    char reg_prefix[30] = "r";
    int i,l,k;
    
    /*for (int i=0; i<cfg_node_id; i++) {
        printf("cfg_node_list: %d , %s, %s, %d, %d.\n",cfg_node_list[i].id,cfg_node_list[i].name,cfg_node_list[i].value,cfg_node_list[i].parent_id,cfg_node_list[i].left_side);
    }*/
    
    for (i=0; i<cfg_node_id; i++) {
        
        //==============handle decl list============
        if (cfg_node_list[i].parent_id==2) {
            char r_varabile[30] = "r_";
            t_code_list[t_code_id].block_id = block_id;
            strcpy(t_code_list[t_code_id].operator,"loadI");
            strcpy(t_code_list[t_code_id].operand1,"0");
            strcat(r_varabile,cfg_node_list[i].name);
            strcpy(t_code_list[t_code_id].destination,r_varabile);
            t_code_id++;
            
        }
        
        //====================handle stmt===============
        else if (cfg_node_list[i].parent_id==3){
            if (strcmp(cfg_node_list[i].name,":=")==0) {    //handle assign
                
                r_child_index=get_r_index(cfg_node_list[i].id);
                l_child_index=get_l_index(cfg_node_list[i].id);
                strcat(r_ass_l,cfg_node_list[l_child_index].value);
                
                if (strcmp(cfg_node_list[r_child_index].name,"readint")==0) { //handle readint
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"readInt");
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    
                }
                
                else if(strcmp(cfg_node_list[r_child_index].name,"ident")==0){
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"i2i");
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    strcat(r_ass_r,cfg_node_list[r_child_index].value);
                    strcpy(t_code_list[t_code_id].operand1,r_ass_r);
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                
                else if(strcmp(cfg_node_list[r_child_index].name,"num")==0){
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"loadI");
                    strcpy(t_code_list[t_code_id].operand1,cfg_node_list[r_child_index].value);
                    inttoreg_id(t_reg_id);
                    strcat(reg_prefix,reg_id);
                    strcpy(t_code_list[t_code_id].destination,reg_prefix);
                    t_code_id++;
                    
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"i2i");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    t_reg_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                
                else if(strcmp(cfg_node_list[r_child_index].name,"boollit")==0){
                    if (strcmp(cfg_node_list[r_child_index].value,"true")==0) {
                        t_code_list[t_code_id].block_id = block_id;
                        strcpy(t_code_list[t_code_id].operator,"loadI");
                        strcpy(t_code_list[t_code_id].operand1,"1");
                        strcat(r_ass_r,cfg_node_list[l_child_index].value);
                        strcpy(t_code_list[t_code_id].destination,r_ass_r);
                        
                        t_code_id++;
                        strcpy(r_ass_l,"r_");
                        strcpy(r_ass_r,"r_");
                    }
                    else{
                        t_code_list[t_code_id].block_id = block_id;
                        strcpy(t_code_list[t_code_id].operator,"loadI");
                        strcpy(t_code_list[t_code_id].operand1,"0");
                        strcat(r_ass_r,cfg_node_list[l_child_index].value);
                        strcpy(t_code_list[t_code_id].destination,r_ass_r);
                        
                        t_code_id++;
                        strcpy(r_ass_l,"r_");
                        strcpy(r_ass_r,"r_");
                    }
                }
                
                else{
                    return_reg_id = handle_exp(cfg_node_list[r_child_index].id);
                    inttoreg_id(return_reg_id);
                    strcat(reg_prefix,reg_id);
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"i2i");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    strcpy(t_code_list[t_code_id].destination,r_ass_l);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    t_reg_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                    
                }
                
                
            }
            
            else if (strcmp(cfg_node_list[i].name,"while")==0) {
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+1);
                char B_pre[5]="B\0";
                strcat(B_pre,reg_id);
                strcpy(t_code_list[t_code_id].destination,B_pre);
                b_relation_list[relationid].parent=block_id;
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                t_code_id++;
                
                block_id++;
                
                int while_exp_index,while_stmt_index;     //2
                int while_b_id,old_t_id;
                int temp_t;
                
                for (l=0; l<cfg_node_id; l++) {
                    if (cfg_node_list[l].parent_id==cfg_node_list[i].id) {
                        if (strcmp(cfg_node_list[l].name,"stmt")==0) {
                            while_stmt_index=l;
                        }
                        else{
                            while_exp_index=l;
                        }
                    }
                }
                
                return_reg_id=handle_exp(cfg_node_list[while_exp_index].id);
                inttoreg_id(return_reg_id);
                t_code_list[t_code_id].block_id = block_id;
                temp_t=t_code_id;
                strcpy(t_code_list[t_code_id].operator,"cbr");
                strcat(reg_prefix,reg_id);
                strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                char dest1[5]="B\0";
                inttoreg_id(block_id+1);
                strcat(dest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,dest1);
                old_t_id=t_code_id;
                
                t_code_id++;
                strcpy(reg_prefix,"r");
                
                
                b_relation_list[relationid].parent=block_id;
                b_relation_list[relationid].child=block_id+1;    //2->3
                relationid++;
                
                
                while_b_id=block_id;                             //keep 2
                block_id++;                //3
                return_reg_id=handle_state(cfg_node_list[while_stmt_index].id);
                strcpy(dest1,"B\0");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(while_b_id);
                strcat(dest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,dest1);
                t_code_id++;
                b_relation_list[relationid].parent=block_id;  //go back while blcok
                b_relation_list[relationid].child=while_b_id;
                relationid++;
                
                block_id++;
                char dest2[5]="B\0";
                inttoreg_id(block_id);
                strcat(dest2,reg_id);
                strcpy(t_code_list[temp_t].destination2,dest2);
                
                b_relation_list[relationid].parent=while_b_id;  //2->last
                b_relation_list[relationid].child=block_id;
                relationid++;
            }
            
            else if (strcmp(cfg_node_list[i].name,"if")==0) {
                //printf("test point!");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+1);
                char C_pre[5]="B\0";
                strcat(C_pre,reg_id);
                strcpy(t_code_list[t_code_id].destination,C_pre);
                b_relation_list[relationid].parent=block_id;
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                t_code_id++;
                
                block_id++;
                
                int if_exp_index,if_then_index,if_else_index;
                
                
                for (l=0; l<cfg_node_id; l++) {
                    if (cfg_node_list[l].parent_id==cfg_node_list[i].id) {
                        if (strcmp(cfg_node_list[l].name,"then")==0) {
                            if_then_index=l;
                        }
                        else if (strcmp(cfg_node_list[l].name,"else")==0) {
                            if_else_index=l;
                        }
                        else{
                            if_exp_index=l;
                        }
                    }
                }
                
                int cbr_id,if_b_id, then_relation_id;    //5
                
                return_reg_id=handle_exp(cfg_node_list[if_exp_index].id); // 5
                inttoreg_id(return_reg_id);
                t_code_list[t_code_id].block_id = block_id;
                cbr_id=t_code_id;
                strcpy(t_code_list[t_code_id].operator,"cbr");
                strcat(reg_prefix,reg_id);
                strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                char idest1[5]="B\0";
                inttoreg_id(block_id+1);
                strcat(idest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,idest1);
                t_code_id++;
                
                strcpy(reg_prefix,"r");
                
                b_relation_list[relationid].parent=block_id;   //if to then 5->6
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                
                if_b_id=block_id;
                block_id++;
                b_relation_list[relationid].parent=block_id;  //6->
                then_relation_id=relationid;
                
                return_reg_id=handle_state(cfg_node_list[if_then_index].id);
                strcpy(idest1,"B\0");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+2);
                strcat(idest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,idest1);
                t_code_id++;
                block_id++;
                relationid++;
                
                b_relation_list[relationid].parent=if_b_id;
                b_relation_list[relationid].child=block_id;        //5->7
                relationid++;
                

                char idest2[5]="B\0";
                inttoreg_id(block_id);
                strcat(idest2,reg_id);
                strcpy(t_code_list[cbr_id].destination2,idest2);
                
                
                
                
                return_reg_id=handle_state(cfg_node_list[if_else_index].id);
                
                strcpy(idest1,"B\0");
                t_code_list[t_code_id].block_id = block_id;
                strcpy(t_code_list[t_code_id].operator,"jumpI");
                inttoreg_id(block_id+1);
                strcat(idest1,reg_id);
                strcpy(t_code_list[t_code_id].destination,idest1);
                t_code_id++;
                b_relation_list[relationid].parent=block_id;   //7->8
                b_relation_list[relationid].child=block_id+1;
                relationid++;
                b_relation_list[then_relation_id].child=block_id+1; //6->8
                block_id++;
            }
            
            else if (strcmp(cfg_node_list[i].name,"writeint")==0) {
                r_child_index=get_r_index(cfg_node_list[i].id);
                
                if (strcmp(cfg_node_list[r_child_index].name,"ident")==0) {
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"writeInt");
                    strcat(r_ass_r,cfg_node_list[r_child_index].value);
                    strcpy(t_code_list[t_code_id].operand1,r_ass_r);
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                else if (strcmp(cfg_node_list[r_child_index].name,"num")==0){
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"loadI");
                    strcpy(t_code_list[t_code_id].operand1,cfg_node_list[r_child_index].value);
                    inttoreg_id(t_reg_id);
                    strcat(reg_prefix,reg_id);
                    strcpy(t_code_list[t_code_id].destination,reg_prefix);
                    t_code_id++;
                    
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"writeInt");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    t_reg_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                }
                else{
                    return_reg_id = handle_exp(cfg_node_list[r_child_index].id);
                    inttoreg_id(return_reg_id);
                    strcat(reg_prefix,reg_id);
                    t_code_list[t_code_id].block_id = block_id;
                    strcpy(t_code_list[t_code_id].operator,"writeInt");
                    strcpy(t_code_list[t_code_id].operand1,reg_prefix);
                    
                    strcpy(reg_prefix,"r");
                    strcpy(reg_id,"\0");
                    t_code_id++;
                    strcpy(r_ass_l,"r_");
                    strcpy(r_ass_r,"r_");
                    
                }
                
                
            }
        }
    }
    
    //==================output cfg===========================
    if (block_id==1) {
        fprintf(cfgoutput,"digraph graphviz { node [shape = none]; edge [tailport = s]; entry ");
        fprintf(cfgoutput,"subgraph cluster { color=\"/x11/white\" n%d [label=\"\n",block_id-1);
        fprintf(cfgoutput,"B%d\n",block_id);
        for (k=0; k<t_code_id; k++) {
            if(t_code_list[k].block_id==block_id){
                if (strcmp(t_code_list[k].operator,"loadI")==0) {
                    fprintf(cfgoutput,"%s %s => %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].destination);
                }
                else if (strcmp(t_code_list[k].operator,"readInt")==0) {
                    fprintf(cfgoutput,"%s  => %s\n",t_code_list[k].operator,t_code_list[k].destination);
                }
                else if (strcmp(t_code_list[k].operator,"writeInt")==0) {
                    fprintf(cfgoutput,"%s %s\n",t_code_list[k].operator,t_code_list[k].operand1);
                }
                else {
                fprintf(cfgoutput,"%s %s %s => %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].operand2,t_code_list[k].destination);
                }
            }
        }
        fprintf(cfgoutput,"exit\",fillcolor=\"/x11/white\",shape=box] }\n");
        fprintf(cfgoutput,"entry -> n%d \n",block_id-1);
        fprintf(cfgoutput,"n%d -> exit }",block_id-1);
    }
    else {
        int m;
        fprintf(cfgoutput,"digraph graphviz { node [shape = none]; edge [tailport = s]; entry ");
        for (m=1; m<block_id; m++) {
            fprintf(cfgoutput,"subgraph cluster { color=\"/x11/white\" n%d [label=\"\n",m-1);
            fprintf(cfgoutput,"B%d\n",m);
            for (k=0; k<t_code_id; k++) {
                if(t_code_list[k].block_id==m){
                    if (strcmp(t_code_list[k].operator,"loadI")==0) {
                        fprintf(cfgoutput,"%s %s => %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].destination);
                    }
                    else if (strcmp(t_code_list[k].operator,"readInt")==0) {
                        fprintf(cfgoutput,"%s  => %s\n",t_code_list[k].operator,t_code_list[k].destination);
                    }
                    else if (strcmp(t_code_list[k].operator,"writeInt")==0) {
                        fprintf(cfgoutput,"%s %s\n",t_code_list[k].operator,t_code_list[k].operand1);
                    }
                    else if(strcmp(t_code_list[k].operator,"cbr")==0){
                        fprintf(cfgoutput,"%s %s -> %s , %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].destination,t_code_list[k].destination2);
                    }
                    else if(strcmp(t_code_list[k].operator,"jumpI")==0){
                        fprintf(cfgoutput,"%s -> %s\n",t_code_list[k].operator,t_code_list[k].destination);
                    }
                    else {
                        fprintf(cfgoutput,"%s %s %s => %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].operand2,t_code_list[k].destination);
                    }
                }
            }
            fprintf(cfgoutput,"\",fillcolor=\"/x11/white\",shape=box] }\n");
            
        }

        fprintf(cfgoutput,"subgraph cluster { color=\"/x11/white\" n%d [label=\"\n",block_id-1);
        fprintf(cfgoutput,"B%d\n",block_id);
        for (k=0; k<t_code_id; k++) {
            if(t_code_list[k].block_id==block_id){
                if (strcmp(t_code_list[k].operator,"loadI")==0) {
                    fprintf(cfgoutput,"%s %s => %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].destination);
                }
                else if (strcmp(t_code_list[k].operator,"readInt")==0) {
                    fprintf(cfgoutput,"%s  => %s\n",t_code_list[k].operator,t_code_list[k].destination);
                }
                else if (strcmp(t_code_list[k].operator,"writeInt")==0) {
                    fprintf(cfgoutput,"%s %s\n",t_code_list[k].operator,t_code_list[k].operand1);
                }
                else if(strcmp(t_code_list[k].operator,"cbr")==0){
                    fprintf(cfgoutput,"%s %s -> %s , %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].destination,t_code_list[k].destination2);
                }
                else if(strcmp(t_code_list[k].operator,"jumpI")==0){
                    fprintf(cfgoutput,"%s -> %s\n",t_code_list[k].operator,t_code_list[k].destination);
                }
                else {
                    fprintf(cfgoutput,"%s %s %s => %s\n",t_code_list[k].operator,t_code_list[k].operand1,t_code_list[k].operand2,t_code_list[k].destination);
                }
            }
        }
        fprintf(cfgoutput,"exit\",fillcolor=\"/x11/white\",shape=box] }\n");
        
        fprintf(cfgoutput,"entry -> n0\n");
        int u;
        for (u=0; u<relationid; u++) {
            fprintf(cfgoutput,"n%d -> n%d\n",b_relation_list[u].parent-1,b_relation_list[u].child-1);
        }
        fprintf(cfgoutput,"n%d -> exit }",block_id-1);
        
        
    }
    
    
    printf("==============Please reveiw CFG output under workdir!=========\n");
    
    
}

//=====================output the assembly code===========================
void codegen(){
    /*printf("print out t address list to verify=========\n");
    for (int i=0; i<t_code_id; i++) {
        printf("t_address_list: %d , %s, %s, %s, %s.\n",t_code_list[i].block_id,t_code_list[i].operator,t_code_list[i].operand1,t_code_list[i].operand2,t_code_list[i].destination);
    }*/
    
    fprintf(codeoutput,"    .data\n");
    fprintf(codeoutput,"newline:    .asciiz \"\\n\" \n");
    fprintf(codeoutput,"    .text\n");
    fprintf(codeoutput,"    .globl main\n");
    fprintf(codeoutput,"main:\n");
    fprintf(codeoutput,"    li $fp 0x7ffffffc \n");
    fprintf(codeoutput,"\n");
    
    int pivor = 0;
    char g_reg[3] = "s";
    int old_b = 0;
    int base = 0;
    int g_pivor;
    int s;
    int opd1,opd2,dest1,dest2;
   
    
    //handle decl
    while (strcmp(t_code_list[pivor].operator,"loadI")==0 && strncmp(t_code_list[pivor].destination,"r_",2)==0) {
        if (t_code_list[pivor].block_id!=old_b) {
            fprintf(codeoutput,"B%d:",t_code_list[pivor].block_id);
            fprintf(codeoutput,"\n");
            old_b=t_code_list[pivor].block_id;
        }
        
        strcpy(g_reg_list[g_reg_id].g_var,t_code_list[pivor].destination);
        g_reg_list[g_reg_id].pivor=0-pivor*4;
        
        fprintf(codeoutput,"    li $t0, 0 \n");
        fprintf(codeoutput,"    sw $t0, %d($fp) \n",g_reg_list[g_reg_id].pivor);
        fprintf(codeoutput,"\n");
        
        g_reg_id++;
        pivor++;
    }
    
    base = pivor;
    
    while (pivor<t_code_id) {
        if (t_code_list[pivor].block_id!=old_b) {
            fprintf(codeoutput,"B%d:",t_code_list[pivor].block_id);
            fprintf(codeoutput,"\n");
            old_b=t_code_list[pivor].block_id;
        }
        
        if (strcmp(t_code_list[pivor].operator,"readInt")==0) {   //handle readint
            
            for (s=0; s<g_reg_id; s++) {
                if (strcmp(t_code_list[pivor].destination,g_reg_list[s].g_var)==0) {
                    g_pivor = s;
                    break;
                }
            }
            // find  variable address
            fprintf(codeoutput,"    li $v0, 5 \n");
            fprintf(codeoutput,"    syscall \n");
            fprintf(codeoutput,"    add $t0, $v0, $zero \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-g_pivor*4);
            fprintf(codeoutput,"\n");
        }
        else if (strcmp(t_code_list[pivor].operator,"writeInt")==0) {
            if (strncmp(t_code_list[pivor].operand1,"r_",2)==0) {
                for (s=0; s<g_reg_id; s++) {
                    if (strcmp(t_code_list[pivor].operand1,g_reg_list[s].g_var)==0) {
                        g_pivor = s;
                        break;
                    }
                }
                // find  variable address
            }
            else {
                g_pivor=base+regtoadd(t_code_list[pivor].operand1);
            }
            
            fprintf(codeoutput,"    li $v0, 1 \n");
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-g_pivor*4);
            fprintf(codeoutput,"    add $a0, $t1, $zero\n");
            fprintf(codeoutput,"    syscall \n");
            fprintf(codeoutput,"    li $v0, 4 \n");
            fprintf(codeoutput,"    la $a0, newline \n");
            fprintf(codeoutput,"    syscall \n");
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"loadI")==0){
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    li $t0, %s \n",t_code_list[pivor].operand1);
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"i2i")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    add $t0, $t1, $zero \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cbr")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            fprintf(codeoutput,"    lw $t0, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    bne $t0, $zero, %s \n",t_code_list[pivor].destination);
            fprintf(codeoutput,"\n");
            fprintf(codeoutput,"    j %s \n",t_code_list[pivor].destination2);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"jumpI")==0){
            fprintf(codeoutput,"    j %s \n",t_code_list[pivor].destination);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"mult")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    mul $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"div")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    divu $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"mod")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    remu $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"add")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    addu $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"sub")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    subu $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_E")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    seq $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_NE")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    sne $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_GT")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    sgt $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_LS")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    slt $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_GE")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    sge $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_LE")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput,"    sle $t0, $t1, $t2 \n");
            fprintf(codeoutput,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput,"\n");
            
        }
        
        pivor++;
    }
    
    
    fprintf(codeoutput,"    li $v0, 10 \n");
    fprintf(codeoutput,"    syscall \n");
}


void optgen(){
    
    
    /*for (int i=0; i<c_pro_id; i++) {
     printf("c_pro_list: %s , %d.\n",c_pro_list[i].var_name,c_pro_list[i].value);
     }*/
    
    //=================out put======================
    fprintf(codeoutput_o,"    .data\n");
    fprintf(codeoutput_o,"newline:    .asciiz \"\\n\" \n");
    fprintf(codeoutput_o,"    .text\n");
    fprintf(codeoutput_o,"    .globl main\n");
    fprintf(codeoutput_o,"main:\n");
    fprintf(codeoutput_o,"    li $fp 0x7ffffffc \n");
    fprintf(codeoutput_o,"\n");
    
    int pivor = 0;
    char g_reg[3] = "s";
    int old_b = 0;
    int base = 0;
    int g_pivor;
    int s;
    int opd1,opd2,dest1,dest2;
    
    
    //handle decl
    while (strcmp(t_code_list[pivor].operator,"loadI")==0 && strncmp(t_code_list[pivor].destination,"r_",2)==0) {
        if (t_code_list[pivor].block_id!=old_b) {
            fprintf(codeoutput_o,"B%d:",t_code_list[pivor].block_id);
            fprintf(codeoutput_o,"\n");
            old_b=t_code_list[pivor].block_id;
        }
        
        strcpy(g_reg_list[g_reg_id].g_var,t_code_list[pivor].destination);
        g_reg_list[g_reg_id].pivor=0-pivor*4;
        
        fprintf(codeoutput_o,"    li $t0, 0 \n");
        fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",g_reg_list[g_reg_id].pivor);
        fprintf(codeoutput_o,"\n");
        
        g_reg_id++;
        pivor++;
    }
    
    base = pivor;
    
    while (pivor<t_code_id) {
        if (t_code_list[pivor].block_id!=old_b) {
            fprintf(codeoutput_o,"B%d:",t_code_list[pivor].block_id);
            fprintf(codeoutput_o,"\n");
            old_b=t_code_list[pivor].block_id;
        }
        
        if (strcmp(t_code_list[pivor].operator,"readInt")==0) {   //handle readint
            
            for (s=0; s<g_reg_id; s++) {
                if (strcmp(t_code_list[pivor].destination,g_reg_list[s].g_var)==0) {
                    g_pivor = s;
                    break;
                }
            }
            // find  variable address
            fprintf(codeoutput_o,"    li $v0, 5 \n");
            fprintf(codeoutput_o,"    syscall \n");
            fprintf(codeoutput_o,"    add $t0, $v0, $zero \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-g_pivor*4);
            fprintf(codeoutput_o,"\n");
        }
        else if (strcmp(t_code_list[pivor].operator,"writeInt")==0) {
            if (strncmp(t_code_list[pivor].operand1,"r_",2)==0) {
                for (s=0; s<g_reg_id; s++) {
                    if (strcmp(t_code_list[pivor].operand1,g_reg_list[s].g_var)==0) {
                        g_pivor = s;
                        break;
                    }
                }
                // find  variable address
            }
            else {
                g_pivor=base+regtoadd(t_code_list[pivor].operand1);
            }
            
            fprintf(codeoutput_o,"    li $v0, 1 \n");
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-g_pivor*4);
            fprintf(codeoutput_o,"    add $a0, $t1, $zero\n");
            fprintf(codeoutput_o,"    syscall \n");
            fprintf(codeoutput_o,"    li $v0, 4 \n");
            fprintf(codeoutput_o,"    la $a0, newline \n");
            fprintf(codeoutput_o,"    syscall \n");
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"loadI")==0){
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    li $t0, %s \n",t_code_list[pivor].operand1);
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"i2i")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    add $t0, $t1, $zero \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cbr")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            fprintf(codeoutput_o,"    lw $t0, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    bne $t0, $zero, %s \n",t_code_list[pivor].destination);
            fprintf(codeoutput_o,"\n");
            fprintf(codeoutput_o,"    j %s \n",t_code_list[pivor].destination2);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"jumpI")==0){
            fprintf(codeoutput_o,"    j %s \n",t_code_list[pivor].destination);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"mult")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    mul $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"div")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    divu $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"mod")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    remu $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"add")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    addu $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"sub")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    subu $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_E")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    seq $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_NE")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    sne $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_GT")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    sgt $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_LS")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    slt $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_GE")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    sge $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        else if (strcmp(t_code_list[pivor].operator,"cmp_LE")==0){
            opd1=allregtoadd(t_code_list[pivor].operand1,base);
            opd2=allregtoadd(t_code_list[pivor].operand2,base);
            dest1=allregtoadd(t_code_list[pivor].destination,base);
            fprintf(codeoutput_o,"    lw $t1, %d($fp) \n",0-opd1*4);
            fprintf(codeoutput_o,"    lw $t2, %d($fp) \n",0-opd2*4);
            fprintf(codeoutput_o,"    sle $t0, $t1, $t2 \n");
            fprintf(codeoutput_o,"    sw $t0, %d($fp) \n",0-dest1*4);
            fprintf(codeoutput_o,"\n");
            
        }
        
        pivor++;
    }
    
    
    fprintf(codeoutput_o,"    li $v0, 10 \n");
    fprintf(codeoutput_o,"    syscall \n");
}

//==============================Main Function===========================


int main(int argc, char **argv)
{
	/*-------------declare area----------------------------------*/
    char *temp_name = argv[1];
    int end;
    int i=0;
    
    while (temp_name[i]!= '.') {
        file_name[i]=temp_name[i];
        i++;
    }
    file_name[i++]='.';
    file_name[i++]='t';
    file_name[i++]='o';
    file_name[i++]='k';
    file_name[i]='\0';
    
    i=0;
    
    while (temp_name[i]!= '.') {
        ast_name[i]=temp_name[i];
        i++;
    }
    ast_name[i++]='.';
    ast_name[i++]='a';
    ast_name[i++]='s';
    ast_name[i++]='t';
    ast_name[i++]='.';
    ast_name[i++]='d';
    ast_name[i++]='o';
    ast_name[i++]='t';
    ast_name[i]='\0';
    
    i=0;
    while (temp_name[i]!= '.') {
        cfg_name[i]=temp_name[i];
        i++;
    }
    cfg_name[i++]='.';
    cfg_name[i++]='3';
    cfg_name[i++]='A';
    cfg_name[i++]='.';
    cfg_name[i++]='c';
    cfg_name[i++]='f';
    cfg_name[i++]='g';
    cfg_name[i++]='.';
    cfg_name[i++]='d';
    cfg_name[i++]='o';
    cfg_name[i++]='t';
    cfg_name[i]='\0';
    
    i=0;
    while (temp_name[i]!= '.') {
        ass_name[i]=temp_name[i];
        i++;
    }
    ass_name[i++]='.';
    ass_name[i++]='s';
    ass_name[i]='\0';
    
    i=0;
    
    while (temp_name[i]!= '.') {
        ass_name_o[i]=temp_name[i];
        i++;
    }
    ass_name_o[i++]='_';
    ass_name_o[i++]='o';
    ass_name_o[i++]='.';
    ass_name_o[i++]='s';
    ass_name_o[i]='\0';
    
    i=0;
    
    //printf("Captured file name:%s \n",file_name);

    if (temp_name==NULL){
        printf("NO source file is provided, please input source file name.\n");
        exit(0);
    }
    else {
        printf("---------Compiler begin---------\n");
        if ( (SourcefPtr = fopen(temp_name, "r")) == NULL ) {
            printf("Cannot open source file %s.\n", temp_name);
            exit(0);
        }
        else{
            printf("Source file %s is open correctly.\n", temp_name);
        }
        
    }
    
    if ((lexicaloutput = fopen(file_name,"wb")) == NULL) {
        printf("Cannot create token output file.Please check the previlige.\n");
    }; //ready to output token
    
    if ((scannererror = fopen("scanner_error.txt","w")) == NULL) {
        printf("Cannot open scanner_error.txt file. Please check it or create a new one.\n");
    }; //ready to output error
		

	/*---------Check if file empty-----------*/

	fseek(SourcefPtr, 0, SEEK_END);
	if (ftell(SourcefPtr) == 0) {
		printf("File is empty.\n");
		exit(0);
	} else {
		rewind(SourcefPtr);
	}

	/*---------Check end-------------*/


	/*---------Lexical scan start-------------*/
    printf("------Lexical scan begin!------ \n");
	
    end=lexicalscanner(SourcefPtr);

	/*---------Lexical scan end-------------*/
    
    
    if (error_list[0].name[0]== '0') {
        printf("------Lexical scan has no error! Token list could be reviewed in %s under workdir! ------\n", file_name);
        goto paserblock;
    }
    else{
        for (i=0; i<errorid; i++) {
            printf("ERROR %d: %s %s in line %d. \n", i, error_list[i].name, error_list[i].info, error_list[i].line);
        }
        printf("------Above error information could be reviewed in scanner_error.txt under workdir! ------\n");
        goto endofmain;
    }
    
    paserblock: ;
    if ((paseroutput = fopen(ast_name,"wb")) == NULL) {
        printf("Cannot create AST output file.Please check the previlige.\n");
    }
    else{
        printf("------Paser started!------ \n");
    }; //ready to output AST
    
    paserscanner();
    fclose(paseroutput);
    /*for (i=0; i<g_viarable_id; i++) {
        printf("Global Viarable %d: %s %s. \n", i, g_viarable_list[i].name, g_viarable_list[i].viatype);
    }*/
    
    
    
    if (sematic_error==0) {
        if ((cfgoutput = fopen(cfg_name,"wb")) == NULL) {
            printf("Cannot create CFG output file.Please check the previlige.\n");
        }
        else{
            printf("------CFG Generator started!------ \n");
        };
        
        cfggen();
        fclose(cfgoutput);
        
        
        
        if ((codeoutput_o = fopen(ass_name_o,"wb")) == NULL) {
            printf("Cannot create optimization output file.Please check the previlige.\n");
        }
        else{
            printf("=======Optimized compilation started, new <name>_o.s would be generated!=============\n");
        };
        optgen();
        fclose(codeoutput_o);
        printf("=======Optimized compilation finished, Pleae review <name>_o.s under workdir!=========\n");
    }
    else{
        printf("There is a type checking error. Please review the ast.dot file to correct it. code generating aborted.\n");
    }
    
    
    endofmain: ;
	fclose(SourcefPtr);
    fclose(lexicaloutput);
    fclose(scannererror);

	return 0;
}




