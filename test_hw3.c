/* Evan Hsia, ehsia1, Homework 3 test functions */

#include "hw3.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

void test_printCat(struct courseID *course)
{
	int num = 9;
	assert(printCatalog(course, num));
	num = 8;
	assert(printCatalog(course, num));
}

void test_printCourse(struct courseID *course)
{
	char id[] = "EN.600.105";
	int num = 9;
	assert(specCourse(course, num, id));
	char id2[] = "EN.440.440";
	assert(!specCourse(course, num, id2));
}

void test_changeTitle(struct courseID *course)
{
	char id[] = "EN.550.171";
	int num = 9;
	char new_title[] = "I Love Penguins";
	struct node *head = NULL;
	assert(newTitle(course, num, id, new_title, head));
	printCatalog(course, num);
	char id2[] = "EN.440.440";
	assert(!newTitle(course, num, id2, new_title, head));
}

void test_changeCred(struct courseID *course)
{
	char id[] = "EN.600.120";
	int num = 9;
	char credit[] = "2.5";
	struct node *head = NULL;
	assert(newCredit(course, num, id, credit, head));
	printCatalog(course, num);
	char id2[] = "AS.200.150";
	assert(!newCredit(course, num, id2, credit, head));
}

int main()
{
	FILE *in = fopen("test.txt", "r");
	int lines = 9;
	struct courseID *course = malloc(lines * sizeof(struct courseID));
        char *pos;
        for (int i = 0; i < lines; i++) {
                fgets(course[i].division, 3, in);
                char point[2] = {'\0'};
                fgets(point, 2, in);
                char temp[4] = {'\0'};
                fgets(temp, 4, in);
                course[i].courseDep = atoi(temp);
                fgets(point, 2, in);
                fgets(temp, 4, in);
                course[i].courseNum = atoi(temp);
                fgets(point, 2, in);
                fgets(temp, 4, in);
                course[i].credit = atof(temp);
                fgets(point, 2, in);
                fgets(course[i].title, 33, in);
                if ((pos = strchr(course[i].title, '\n')) != NULL) {
                        *pos = '\0';
                }
        }
        fclose(in);
	test_printCat(course);
	test_printCourse(course);
	test_changeTitle(course);
	test_changeCred(course);
	free(course);
	printf("success\n");
	return 0;
}
