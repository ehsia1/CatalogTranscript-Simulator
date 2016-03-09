#include "hw3.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct node *new_node(char id[], char term[], struct courseID *course, int lines, struct node *cur) //fix to put them in order (previous pointer, temp pointer, relink)
{
        struct node *transcript = malloc(sizeof(struct node));
	struct node *temp;
        transcript->next = cur;

        char div[3] = {'\0'};
        char de[4] = {'\0'};
        char nu[4] = {'\0'};
        for (int j = 0; j < 2; j++) {
                div[j] = id[j];
        }
        for (int k = 0; k < 3; k++) {
                de[k] = id[k+3];
                nu[k] = id[k+7];
        }
        int dep = atoi(de);
        int num = atoi(nu);
        int count = 0;
        for (int i = 0; i < lines; i++) {
                if (strcmp(course[i].division, div) == 0 && course[i].courseDep == dep && course[i].courseNum == num) {
                        count++;
                        strcpy(transcript->student.division, div);
                        transcript->student.courseDep = dep;
                        transcript->student.courseNum = num;
                        transcript->student.credit = course[i].credit;
                        strcpy(transcript->student.title, course[i].title);
                }
        }
        if (count == 0) {
                puts("invalid");
		temp = transcript->next;
		free(transcript);
                return temp;
        }

        char semester[7] = {'\0'};
        char grade[3] = {'\0'};

        for (int m = 0; m < 6; m++) {
                semester[m] = term[m];
        }

        for (int n = 0; n < 2; n++) {
                grade[n] = term[n+7];
        }

        strcpy(transcript->term, semester);
        strcpy(transcript->grade, grade);

        char *pos;
        if ((pos = strchr(transcript->grade, '\n')) != NULL) {
                *pos = '\0';
        }

        while (cur != NULL) {
                if (strcmp(transcript->student.division, cur->student.division) == 0 && transcript->student.courseDep == cur->student.courseDep && transcript->student.courseNum
                  == cur->student.courseNum && strcmp(transcript->term, cur->term) == 0) {
                        puts("present");
  			temp = transcript->next;
			free(transcript);
                        return temp;
                }
                cur = cur->next;
        }
	puts("added");
        return transcript;
}

struct node *remove_node(char user[], char user2[], struct node *cur)
{
        if (cur == NULL) {
		puts("transcript empty");
                return cur;
        }
        struct node *previous = cur;
        struct node *transcript = cur;
        char div[3] = {'\0'};
        char de[4] = {'\0'};
        char nu[4] = {'\0'};
        for (int j = 0; j < 2; j++) {
                div[j] = user[j];
        }
        for (int k = 0; k < 3; k++) {
                de[k] = user[k+3];
                nu[k] = user[k+7];
        }
        int dep = atoi(de);
        int num = atoi(nu);
        char semester[7] = {'\0'};
        int count = 0;

        for (int m = 0; m < 6; m++) {
                semester[m] = user2[m];
        }

        if (strcmp(transcript->student.division, div) == 0 && transcript->student.courseDep == dep && transcript->student.courseNum == num && strcmp(transcript->term, semester)
           == 0) {
                transcript = cur->next;
                puts("removed");
                return transcript;
        }
        int a = 0; //counter to run through linked list
        while (cur != NULL) {
                if (strcmp(cur->student.division, div) == 0 && cur->student.courseDep == dep && cur->student.courseNum == num && strcmp(cur->term, semester) == 0) {
                        previous->next = cur->next;
                        count++;
                        free(cur);
                        puts("removed");
                }
                if (a == 0) {
                        cur = cur->next;
                }
                if (a >= 1) {
                        cur = cur->next;
                        previous = previous->next;
                }
                a++;
        }
        if (count == 0) {
                puts("absent");
        }
        return transcript;
}

struct node *reorderList(struct node *cur)
{
        struct node *temp1, *temp2, *newHead, *prev, *first;
        newHead = NULL;
        while (cur != NULL) {
                prev = NULL;
                first = temp1 = cur;
                temp2 = cur->next;
                while (temp2 != NULL) { //compare two nodes at a time, taking the first node of cur and comparing with all others
                        char temp[7] = {'\0'};
                        strcpy(temp, temp2->term);
                        char yearChar[5] = {'0'};
                        for (int i = 0; i < 4; i++) {
                                yearChar[i] = temp[i];
                        }
                        float yearNext = atof(yearChar);
                        char semesterNext[2] = {'\0'};
                        semesterNext[0] = temp[5];
			float semNext;
			float semNow;
			if (semesterNext[0] == 'F') {
				semNext = 1;
			} else if (semesterNext[0] == 'S') {
				semNext = 0;
			}

                        strcpy(temp, first->term);
                        for (int i = 0; i < 4; i++) {
                                yearChar[i] = temp[i];
                        }
                        float yearNow = atof(yearChar);
                        char semesterNow[2] = {'\0'};
                        semesterNow[0] = temp[5];
			if (semesterNow[0] == 'F') {
				semNow = .1;
			} else if (semesterNow[0] == 'S') {
				semNow = .0;
			}

			float termNow = yearNow + semNow;
			float termNext = yearNext + semNext;

                        if (termNow > termNext) {
                                first = temp2;
                                prev = temp1;
                        }
                        temp1 = temp2;
                        temp2 = temp2->next;
                }

                if (prev == NULL) { //allows the loop to go through again
                        cur = first->next;
                } else { //creates a new link
                        prev->next = first->next;
                }
                first->next = NULL;
                if (newHead == NULL) {
                        newHead = first;
                } else { //finishes the sorting by pushing the nodes down the line in newHead
                        temp1 = newHead;
                        while (temp1->next != NULL) {
                                temp1 = temp1->next;
                        }
                        temp1->next = first;
                }
        }
        return newHead;
}

void printTranscript(struct node *head) //need to reorder still
{
        int count = 0;
        while(head != NULL) {
		printf("%s.%d.%d %.1f %s %s %s\n", head->student.division, head->student.courseDep, head->student.courseNum, head->student.credit, head->student.title,
		  head->term, head->grade);
                head = head->next;
                count++;
        }
        if (count == 0) {
                puts("transcript empty");
        }
}

void transCourse(char user[], struct node *cur)
{
        char div[3] = {'\0'};
        char de[4] = {'\0'};
        char nu[4] = {'\0'};
        for (int j = 0; j < 2; j++) {
                div[j] = user[j];
        }
        for (int k = 0; k < 3; k++) {
                de[k] = user[k+3];
                nu[k] = user[k+7];
        }
        int dep = atoi(de);
        int num = atoi(nu);
        int count = 0;

        while (cur != NULL) {
                if (strcmp(cur->student.division, div) == 0 && cur->student.courseDep == dep && cur->student.courseNum == num) {
                        printf("%s %s\n", cur->term, cur->grade);
                        count++;
                }
                cur = cur->next;
        }
        if (count == 0) {
                puts("absent");
        }
}

void calcGPA(struct node *cur)
{
        float gpa = 0;
        float credit = 0;
        while (cur != NULL) {
                if (strcmp(cur->grade, "A+") == 0 || strcmp(cur->grade, "A/") == 0) {
                        gpa+=4.0*cur->student.credit;
                } else if (strcmp(cur->grade, "A-") == 0) {
                        gpa+=3.7*cur->student.credit;
                } else if (strcmp(cur->grade, "B+") == 0) {
                        gpa+=3.3*cur->student.credit;
                } else if (strcmp(cur->grade, "B/") == 0) {
                        gpa+=3.0*cur->student.credit;
                } else if (strcmp(cur->grade, "B-") == 0) {
                        gpa+=2.7*cur->student.credit;
                } else if (strcmp(cur->grade, "C+") == 0) {
                        gpa+=2.3*cur->student.credit;
                } else if (strcmp(cur->grade, "C/") == 0) {
                        gpa+=2.0*cur->student.credit;
                } else if (strcmp(cur->grade, "C-") == 0) {
                        gpa+=1.7*cur->student.credit;
                } else if (strcmp(cur->grade, "D+") == 0) {
                        gpa+=1.3*cur->student.credit;
                } else if (strcmp(cur->grade, "D/") == 0) {
                        gpa+=1.0*cur->student.credit;
                } else if (strcmp(cur->grade, "D-") == 0 || strcmp(cur->grade, "F/") == 0) {
                        gpa+=0.0;
                } else {
                        gpa+=0.0;
                        credit-=cur->student.credit;
                }
                credit += cur->student.credit;
                cur = cur->next;
        }
        if (credit != 0) {
                gpa = gpa/credit;
        }
        printf("GPA = %.2f\n", gpa);
}

