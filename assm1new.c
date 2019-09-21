/* Solution to comp10002 Assignment 1, 2019 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Joshua Philip Dubar 1086080
   Dated:     9/09/2019

*/
/*Algorithms are Fun! */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* *************************************************** */
/*                     Constants                       */
#define DEFAULT_OFFSET 4 /* default margin size */
#define MAXDELIM 5 /* size of delimiters in strtok */
#define MAXLINE 50 /* default output line max length */
#define MAX 999 /* largest input line length*/
#define FULLSTOP '.' /* fullstop character */
#define BREAK 'b' /* break symbol character */
#define PARAGRAPH 'p' /* paragraph symbol character */
#define LEFT 'l' /* margin size symbol character */
#define WIDTH 'w' /* width size symbol character */
#define NEWLINE '\n' /* new line character */
#define DELIMITERS " \r\n\t" /* delimiters for token */
#define NEWPARA "\n\n" /* creates new paragraph */
#define SPACE ' ' /* space character */
/* *************************************************** */

/* *************************************************** */
/*                  function prototypes                */
void process_line(int *count, int *previous, int *margin, int *width, char *line);
void remove_spaces(char *line, int *offset, int *width, int *count);  
int check_commands(char *line);
void print_spaces(int nn);
void process_break();
void process_paragraph();
void print_spaces(int nn);
int nn(char *line);
/* *************************************************** */

/* main program controls all the action */

int 
main(int argc, char *argv[]) {
    char line[MAX];
    int count = 0, previous=0, margin=DEFAULT_OFFSET, width=MAXLINE;
    print_spaces(DEFAULT_OFFSET);
    /* read in each line and send them off for processing*/
    while (fgets(line, sizeof line, stdin)) {
        process_line(&count, &previous, &margin, &width, line);
    }
    return 0;
}

/* perform different actions depending on the command, if there is no command we process the text in the line*/

void process_line(int *count, int *previous, int *margin, int *width, char *line) {
    /* test for each command */
    if (line[0] == FULLSTOP) {            
        if (line[1] == LEFT && !*previous) {
            *margin = check_commands(line);
        } else if (line[1] == LEFT) {
            *margin = nn(line);
            print_spaces(*margin);
            return;
        } else if (line[1] == WIDTH && !*previous) {
            *width = check_commands(line);
        } else if (line[1] == WIDTH) {
            *width = nn(line);
            print_spaces(*margin);
            return;
        } else if ((line[1] == BREAK || line[1] == PARAGRAPH) && !*previous) {
            check_commands(line);
        } else if ((line[1] == BREAK || line[1] == PARAGRAPH)) {
            return;
        }
        print_spaces(*margin);
        *previous = 1; 
        *count = 0;
        
    } else if (line[0] != FULLSTOP) {
        remove_spaces(line, margin, width, count);  
        *previous = 0;   
    }
}

/* function to remove spaces and output text  */
void remove_spaces(char *line, int *offset, int *width, int *count) {
    char *token;
    /* choose how to seperate tokens */
    const char s[MAXDELIM] = DELIMITERS;
    token = strtok(line, s);
    /* line by line, remove delimiters and display text to the maximum width of the line */
    while (token != NULL) {
        *count += strlen(token) + 1;
        if (*count-1 > *width) {
            printf("%c", NEWLINE);
            print_spaces(*offset);
            *count = strlen(token)+1;
        } 
        printf("%s ", token);
        token = strtok(NULL, s); 
    }
}
/* check the commands used and performs them */
int check_commands(char *line) {

    if (line[1] == BREAK) {
        process_break();
        return 0;
    } else if (line[1] == PARAGRAPH) {
        process_paragraph();
        return 0;
    /* if .l or .w we want to change the margin size/width, so we return a number */
    } else if (line[1] == LEFT) {
        process_paragraph();
        int i =  nn(line);
        return i;
    } else if (line[1] == WIDTH) {
        process_paragraph();
        int i = nn(line);
        return i;
    }
    return 0;
}

/* process break command */
void process_break() {
    printf("%c", NEWLINE);
}

/* process new paragraph command */
void process_paragraph() {
    printf("%s", NEWPARA);
}

/* print margin */
void print_spaces(int nn) {
    int i;
    for (i=0;i<nn;i++) {
        printf("%c", SPACE);
    }
}

/* return the new size of the margin size/width of text */

int nn(char *line) { 
    char nums[4];
    /* change nn characters to an integer */
    nums[0] = line[3], nums[1] = line[4], nums[2] = line[5];
    int converted;
    converted = atoi(nums);
    return converted;
}