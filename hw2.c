/*
 * ONOMATEPWNYMO 1:KONSOYLAS KONSTANTINOS AEM:02975
 * ONOMATEPWNYMO 2:EVANGELOS BALAMOTIS AEM:02927 
 */

#include "hw2.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void read_txt(char words[][MAX_WORD_LEN],char*words_ptr[][2]){
	
	char help[MAX_WORD_LEN] ={'\0'};
	int i,j,k,l;
	l=0;
	
	for(i=0 ;i < MAX_WORDS ;i++){
		k=1;
		
		scanf(" %s",help);
		
		if(strcmp(help,"") == 0){
			continue;
		}
		
		for(j=0 ;help[j] !='\0' ;j++){
			
			if( (help[j] >= 'A') && (help[j] <= 'Z') ){
				help[j] ='a' + help[j] - 'A';
			}
		}
		
		
		
		for(j=0 ;j<l ;j++){
			
			if(strcmp(words[j],help) == 0 ){
				words_ptr[i][0] = &words[j][0];
				k=0;
			}
		}
			
		if(k){
			strcpy(words[l],help);
			words_ptr[i][0] = &words[l][0];
			l++;
		}
			
		k++;
		
		for(j=0; j<MAX_WORD_LEN ;j++){
			
			help[j] ='\0';
		}
		
		
	}
}

void print_txt (char *words_ptr[][2], int linelen){
	
	int limit;
	char help[MAX_WORD_LEN] = {'\0'};
	
	limit = linelen;

	
	strcpy(help, words_ptr[0][0]);
	help[0] = toupper(help[0]);

	printf("\n\n%s", help);
	linelen = linelen - (strlen(words_ptr[0][0]));
	if(words_ptr[0][1] != NULL){
		strcpy(help, words_ptr[0][1]);
		help[0] = toupper(help[0]);

		printf(" (%s)", help);
		linelen = linelen - (strlen(words_ptr[0][1]) + 3);
	}
	
	for(int i=1 ;i < MAX_WORDS && words_ptr[i][0] != NULL ;i++){
		for(int j=0 ; j < 2 && words_ptr[i][j] ;j++){

			if(strlen(words_ptr[i][j]) + 1 + j*2 <= linelen ){

				//if not first word in line put space
				linelen != limit ? putchar(' ') : linelen++;
				//subtract characters
				linelen = linelen - (strlen(words_ptr[i][j]) + 1 + j*2);

				//synonym specific printing syntax
				if(j){
					putchar('(');
				}
				//

				if(strcmp(words_ptr[i-1][0], ".") !=0 && strcmp(words_ptr[i-1][0], "!") !=0 && strcmp(words_ptr[i-1][0], "?") !=0)
					printf("%s",words_ptr[i][j]);
				else{
					strcpy(help, words_ptr[i][j]);
					help[0] = toupper(help[0]);
					printf("%s",help);
				}

				//synonym specific printing syntax
				if(j){
					putchar(')');
				}
				//

			}
			else{
				putchar('\n');
				linelen = limit;
				j--;
			}

		}
	}

	putchar('\n');

}



void histogram_make(char*words_ptr[][2],int word_count[]){
	
	int i, j, k, word_pos, new_word_pos, first_different_word;
	char*address_track[MAX_WORDS] = {NULL};
	int address_tracked = 0;
	
	first_different_word =0;
	word_pos =0;
	new_word_pos =0;
	i=0;
	address_track[0] = words_ptr[0][0];
	
	for(j=0 ;j<MAX_WORDS ;j++){
		
		if(new_word_pos != word_pos){
			word_pos = new_word_pos;
			i=word_pos;
		}
		else if(word_pos != 0){
			break;
		}
		
		for(first_different_word =0 ;i<MAX_WORDS ;i++){
			
			address_tracked =0;
			
			if(words_ptr[i][0] == NULL){
				break;
			}
			
			
			
			if((words_ptr[word_pos][0] == words_ptr[i][0]) /*&& (first_different_word)*/ ){
				
				word_count[j]++;
				
			
			}
			else if(first_different_word == 1){
				
				
			}
			else {
				for(k=0 ;k<j ;k++){
					if(words_ptr[i][0] == address_track[k]){
						address_tracked =1;
					}
					
				}
				
				
				if(address_tracked != 1){
					new_word_pos =i;
					first_different_word =1;
					address_track[j+1] = words_ptr[i][0];
					
					
				}
			}
		}
		//printf("%d,%s ",word_count[j],address_track[j]);
	}
	
}

void histogram_print(char words[][MAX_WORD_LEN] ,int word_count[]){
	
	int i,j,spaces ,thous ,hund ,dec ,mon;
	
	for(i =0 ;i<MAX_WORDS ;i++){
		
		if(strcmp(words[i],"") == 0){
			continue;
		}
		
		thous = 0; 
		hund = 0;
		dec = 0;
		mon = 0;
		spaces =MAX_WORD_LEN-strlen(words[i]);
		
		printf("\n");
		for(j=0 ;j<spaces ;j++){
			putchar(' ');
		}
		
		printf("%s: ",words[i]);
		
		thous = word_count[i] /1000;
		for(j=0 ;j<thous ;j++){
			printf("$");
		}
		
		hund = word_count[i] /100;
		hund = hund%10;
		for(j=0 ;j<hund ;j++){
			printf("#");
		}
		
		dec = word_count[i] /10;
		dec = dec%10;
		for(j=0 ;j<dec ;j++){
			printf("@");
		}
		
		mon = word_count[i] -(thous*1000) -(hund*100) -(dec*10);
		for(j=0 ;j<mon ;j++){
			printf("*");
		}
		
		
	}
	
	printf("\n");
	
}



void print_synonyms(char *words_ptr[][2], char synonyms[][MAX_WORD_LEN*2]){
	
	int i, j;
	
	for(i=0; i<MAX_WORDS; i++){
		
		if(words_ptr[i][0] == NULL){
			break;
		}
		
		for(j=0; j<MAX_SYNONYMS; j++){
			
			if(words_ptr[i][0] == NULL){
				continue;
			}
			
			if(words_ptr[i] == NULL){
				break;
			}
			
			if(strcmp(*words_ptr[i], synonyms[j]) == 0){
				
				words_ptr[i][1] = synonyms[j];
				words_ptr[i][1] = words_ptr[i][1] + strlen(synonyms[j]) + 1;
			}
		}
	}
}





/**/
int main(int argc, char* argv[]) {
	init_stack_size();
	return hw2_main(argc, argv);
}

/**/
int hw2_main(int argc, char* argv[]) {
	// ADD YOUR CODE HERE  
	
	int i ;
	char words[MAX_WORDS][MAX_WORD_LEN] = {{'\0'}};
	char *words_ptr[MAX_WORDS][2] = {{NULL}};
	int  word_count[MAX_WORDS] ={0};
	char synonyms[MAX_SYNONYMS][MAX_WORD_LEN*2];
	int synonym_file_pos =-1;
	int syn_existance =0;
	
	if(argc<2){
		printf("Incorrect command-line arguments!\n");
		return(0);
	}
	
	for(i=1 ;i<argc ;i++){
		
		if(strcmp(argv[i],"-r") == 0){
			synonym_file_pos = i+1;
			
		}
		
	}
	
	
	for(i=1 ;i<argc && (i!=synonym_file_pos);i++){
		
		if((strcmp(argv[i],"-h") != 0) && (strcmp(argv[i],"-r") != 0) && (strcmp(argv[i],"-p") != 0) && (strcmp(argv[i],"") != 0)){
			printf("Incorrect command-line arguments!\n");
			return(0);
		
		}
		
	}
	read_txt(words ,words_ptr);
	
	for(i=1 ;i<argc ;i++){
		
		if(strcmp(argv[i],"-h") == 0){
			//printf("h ");
			
			
			histogram_make(words_ptr ,word_count);
			
			histogram_print(words ,word_count);
		}
		
	}
	
	for(i=1 ;i<argc ;i++){
		
		if(strcmp(argv[i],"-r") == 0){
			//printf("r ");
			syn_existance = read_synonyms(argv[synonym_file_pos] ,synonyms);
			if (syn_existance == 1){
				print_synonyms(words_ptr, synonyms);
			}
			
		}
	}
	for(i=1 ;i<argc ;i++){
		
		if(strcmp(argv[i],"-p") == 0){
			//printf("p\n");
			
			print_txt(words_ptr, MAX_LINE_LEN);
		}
		
	}
	
	//read_txt(words ,words_ptr);
	
	//print_txt(words_ptr, MAX_LINE_LEN);
	
	//histogram_make(words_ptr ,word_count);
	
	//histogram_print(words ,word_count);

	return 0;
}

//histogram_print fixed









