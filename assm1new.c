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
#define DEFAULT_OFFSET 4
#define MAXDELIM 5
#define MAXLINE 50
#define MAX 999
#define FULLSTOP '.'
#define BREAK 'b'
#define PARAGRAPH 'p'
#define LEFT 'l'
#define WIDTH 'w'

/* *************************************************** */
int count = 0;
/* *************************************************** */
/*                  function prototypes                */
void remove_spaces(char *line, int offset, int width);
int check_commands(char *line);
void print_spaces(int nn);
void process_break();
void process_paragraph();
void print_spaces(int nn);
int nn(char *line);
/* *************************************************** */

int main(int argc, char *argv[]) {
    char line[MAX];
    int previous=0, margin=DEFAULT_OFFSET, width=MAXLINE;
    print_spaces(DEFAULT_OFFSET);
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == FULLSTOP && !previous) {            
            if (line[1] == LEFT) {
                margin = check_commands(line);
                printf("\n%d\n", margin);
            } else if (line[1] == WIDTH) {
                width = check_commands(line);
            } else if (line[1] == BREAK || line[1] == PARAGRAPH) {
                check_commands(line);
            }
            print_spaces(margin);
            previous = 1; 
            count = 0;
        } else if (line[0] != FULLSTOP) {
            remove_spaces(line, margin, width);  
            previous = 0;   
        }
    }
    return 0;
}

void remove_spaces(char *line, int offset, int width) {
    char *token;
    const char s[MAXDELIM] = " \r\n\t";
    token = strtok(line, s);
    while (token != NULL) {
        count += strlen(token) + 1;
        if (count-1 > width) {
            printf("\n");
            print_spaces(offset);
            count = strlen(token)+1;
        } 
        printf("%s ", token);
        token = strtok(NULL, s); 
    }
}

int check_commands(char *line) {
    if (line[1] == BREAK) {
        process_break();
        return 0;
    } else if (line[1] == PARAGRAPH) {
        process_paragraph();
        return 0;
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

void process_break() {
    printf("\n");
}

void process_paragraph() {
    printf("\n\n");
}

void print_spaces(int nn) {
    int i;
    for (i=0;i<nn;i++) {
        printf(" ");
    }
}

int nn(char *line) {
    char nums[3];
    nums[0] = line[3], nums[1] = line[4];
    int converted;
    converted = atoi(nums);
    return converted;
}