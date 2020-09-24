// BETUL CAM 150170058 BLG102E ASSIGNMENT4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_OF_LINES 10000
#define NUM_OF_CHAR 200
struct instruction_s{  
    int step; 
    int index; 
};

char* get_word(char* s, int n){
    char* word =malloc(NUM_OF_CHAR * sizeof(char));
    int i,j=0;
    for(i=0 ;i<n-1; i++)
    {
        while(s[j]!= ' ' && s[j] !='\0')
        {
            j++;
        }
        j++;
    }
    i=0;
    while (s[j] != ' ' && s[j] !='\0'&& s[j] !='.'&& s[j] !=',' && s[j] !=':' && s[j] !=';' && s[j] !='!' && s[j] !='?' && s[j] !='=' && s[j] !='-' && s[j] !='_' && s[j] !='@' && s[j])
    {
        if(s[j] >= 'A' && s[j] <= 'Z'){ // Convert uppercases to lower cases using ascii table
            s[j] = s[j] + 32;
        }
        word[i] = s[j];
        i++;
        j++;
    }
    return word;
}

void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence){
    int j = 0;
    int my_step = -1;
    for (int i = 0; i < n_instructions; i++)
    {
        my_step += instructions[i].step;
        char* word = get_word(lines[my_step], instructions[i].index);
        int k = 0;
        while (word[k] != ' ' && word[k] !='\0')
        {
            sentence[j] = word[k];
            j++;
            k++;
        }
        sentence[j] = ' ';
        j++;
    }
}

int main(int argc, char **argv){
    FILE *book_file = fopen(argv[1], "r");
    FILE *instructions_file = fopen(argv[2], "r");
    if(argc != 3)
    {
        fprintf(stderr, "Usage: ./assignment4 alice.txt instructions.txt\n");
        return EXIT_FAILURE;
    }
    if (book_file == 0 || instructions_file == 0)
    {
        fprintf(stderr, "Failed to open file.\n");
        return EXIT_FAILURE;
    }
    int i = 0;

    char** book = (char**)malloc(NUM_OF_LINES * sizeof(char*));// memory alocated for each line of file    
    for(;i < NUM_OF_LINES; i++){ // memory allocated for each character of lines
        book[i] = (char*)malloc(NUM_OF_CHAR * sizeof(char));
    }
    i=0;
    while(fgets(book[i], NUM_OF_LINES, book_file)) // read book_file and stor in char** book
	{
        book[i][strlen(book[i]) - 1] = '\0';
        i++;
    }
    int  lines = 0;
    char c;
    char last = '\n';
    while (EOF != (c = fgetc(instructions_file))) // 8his loop counts instructions_file excluding the empty lines
    {
        if (c == '\n' && last != '\n')
        {
            ++lines;
        }
        last = c;
    }
    rewind(instructions_file); //turn back to first line  of the file

    struct instruction_s *instructions = (struct instruction_s*)malloc(lines * sizeof (struct instruction_s)); // memory allocated for the struct
    for(i = 0; i < lines ; i++)
    {
        fscanf(instructions_file, "%d %d", &instructions[i].step, &instructions[i].index);
    }

    char* sentence = (char*)malloc(NUM_OF_CHAR * sizeof(char));
    get_sentence(book, instructions, i, sentence);
    printf("%s\n", sentence);

    fclose(book_file);
    book_file = NULL;
    fclose(instructions_file); 
    instructions_file = NULL;
    
    for (i = 0; i < NUM_OF_LINES; i++){ 
        free(book[i]);
        book[i] = NULL;
    }
    free(instructions);
    instructions = NULL;
    free(book);
    book = NULL;
    free(sentence);
    sentence = NULL;
    return EXIT_SUCCESS;
}