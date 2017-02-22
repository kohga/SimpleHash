#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "tom.txt"
#define SIZE 1024
#define TIMES 1000
#define MAX_HASH 256

struct hash_table{
	int enc,cnf;
	char *str;
};
struct hash_table hashtable[256]={0};
char mem[100000];
char *p_newmem = mem;

char *mem_alloc(int length){
	char *p;
	p = p_newmem;
	p_newmem = p_newmem + length;
	return p;
}

char *create_string(char *str){
	char *cp;
	cp = mem_alloc(strlen(str)+1);
	strcpy(cp,str);
	return cp;
}

int hash(char *str){
	int ret=0;
	while(*str){
		if(*str>='A'&&*str<='Z')
			*str=*str-('A'-'a');
		ret += *str;
		str++;
	}
	ret %= MAX_HASH;
	return ret;
}

void dump_ht(){
	int i;
	for(i=0;i<256;i++){
		if(hashtable[i].str){
			printf("[%d] ,",i);
			printf(" %d ,",hashtable[i].enc);
			printf(" %s ,",hashtable[i].str);
			printf(" %d\n",hashtable[i].cnf);
		}
	}
}

int main(int argc, char *argv[]){
	FILE *istream;
	char getstr[SIZE];
	int i,h;

	if((istream = fopen(FILENAME, "r")) == 0 ) {
		fprintf(stderr, "%s\n", "error: can't read file.");
		exit(EXIT_FAILURE);
	}
	
	for(i=0;i<TIMES;i++){
		if(fscanf(istream,"%s",getstr)== EOF )
			break;

		h = hash(getstr);

		if( hashtable[h].enc == 0 ){
			hashtable[h].enc++;
			hashtable[h].str = create_string(getstr);
		} else if( hashtable[h].enc > 0 && !strcmp(hashtable[h].str, getstr) )
			hashtable[h].enc++;
		else
			hashtable[h].cnf++;
	}

	fclose(istream);
	dump_ht();

	return EXIT_SUCCESS;
}
