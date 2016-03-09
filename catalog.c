#include "hw3.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void printCatalog(struct courseID *course, int lines)
{
        int i;
        for (i = 0; i < lines; i++) {
                printf("%s.%d.%d %.1f %s\n", course[i].division, course[i].courseDep, course[i].courseNum, course[i].credit, course[i].title);
        }
}

void specCourse(struct courseID *course, int lines, char user[])
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
        for (int i = 0; i < lines; i++) {
                if (strcmp(course[i].division, div) == 0 && course[i].courseDep == dep && course[i].courseNum == num) {
                        printf("%.1f %s", course[i].credit, course[i].title);
                        count++;
                }
        }
        if (count == 0) {
                puts("absent");
        }
}

void newTitle(struct courseID *course, int lines, char user[], char user2[], struct node *cur)
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
        char *pos;
        if ((pos = strchr(user2, '\n')) != NULL) {
                *pos = '\0';
        }
	for (int i = 0; i < lines; i++) {
                if (strcmp(course[i].division, div) == 0 && course[i].courseDep == dep && course[i].courseNum == num) {
                        count++;
                        strcpy(course[i].title, user2);
			while (cur != NULL) {
				if (strcmp(cur->student.division, div) == 0 && cur->student.courseDep == dep && cur->student.courseNum == num) {
					strcpy(cur->student.title, user2);
				}
				cur = cur->next;
			}
                        puts("updated");
                }
        }
        if (count == 0) {
                puts("absent");
        }
}

void newCredit(struct courseID *course, int lines, char user[], char user2[], struct node *cur)
{
        float cred = atof(user2);
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
        for (int i = 0; i < lines; i++) {
                if (strcmp(course[i].division, div) == 0 && course[i].courseDep == dep && course[i].courseNum == num) {
                        count++;
                        course[i].credit = cred;
			while (cur->next != NULL) {
                                if (strcmp(cur->student.division, div) == 0 && cur->student.courseDep == dep && cur->student.courseNum == num) {
					cur->student.credit = cred;
                                }
                                cur = cur->next;
                        }
                        puts("updated");
                }
        }
        if (count == 0) {
                puts("absent");
        }
}
