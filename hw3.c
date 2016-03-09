/* Evan Hsia, ehsia1, Homework 3 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hw3.h"

int getLines(FILE *in)
{
	char temp[100] = {'\0'};
	int count = 0;
	while (fgets(temp, 100, in) != NULL) {
		count++;
	}
	return count;
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		return 1;
	}

	FILE *in = fopen(argv[1], "r");
	int lines = getLines(in);

	struct courseID *course = malloc(lines * sizeof(struct courseID));
	rewind(in);
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
	char user[100] = {'\0'};
	char user2[100] = {'\0'};
	char input = 'm';
	struct node *head = NULL;
	struct node *temp;
	while (input != 'Q') {
		puts("Please enter your choice: ");
		fgets(user, 100, stdin);
		user[0] = toupper(user[0]);
		switch (user[0]) {
			case 'Q': //quit
				while (head != NULL) {
					temp = head->next;
					free(head);
					head = temp;
				}
				free(course);
				input = 'Q';
				break;
			case 'P': //print catalog
				printCatalog(course, lines);
				break;
			case 'C': //print course
				puts("Please enter the course identifier (xx.ddd.nnn): ");
				fgets(user, 100, stdin);
				for (int i = 0; i < 100; i++) {
					user[i] = toupper(user[i]);
				}
				specCourse(course, lines, user);
				break;
			case 'T': //change title
				puts("Please enter the course identifier (xx.ddd.nnn): ");
				fgets(user, 100, stdin);
				for (int i = 0; i < 100; i++) {
                                        user[i] = toupper(user[i]);
                                }
				puts("Please enter the desired course title (32 characters max): ");
				fgets(user2, 33, stdin);
				newTitle(course, lines, user, user2, head);
				break;
			case 'R': //change credit
				puts("Please enter the course identifier (xx.ddd.nnn): ");
				fgets(user, 100, stdin);
				for (int i = 0; i < 100; i++) {
					user[i] = toupper(user[i]);
				}
				puts("Please enter the desired credits: ");
				fgets(user2, 100, stdin);
				newCredit(course, lines, user, user2, head);
				break;
			case 'A': //add to transcript
				puts("Please enter the course identifier (xx.ddd.nnn): ");
				fgets(user, 100, stdin);
				for (int i = 0; i < 100; i++) {
					user[i] = toupper(user[i]);
				}
				puts("Please enter the semester and grade (yyyy.s Gg): ");
				fgets(user2, 100, stdin);
				for (int j = 0; j < 100; j++) {
					user2[j] = toupper(user2[j]);
				}
				head = new_node(user, user2, course, lines, head); //need to send in a pointer to head and add things in order
				head = reorderList(head);
				break;
			case 'D': //remove from transcript
				puts("Please enter the course identifier (xx.ddd.nnn): ");
				fgets(user, 100, stdin);
				for (int i = 0; i < 100; i++) {
					user[i] = toupper(user[i]);
				}
				puts("Please enter the semester(yyyy.s): ");
				fgets(user2, 100, stdin);
				for (int j = 0; j < 100; j++) {
					user2[j] = toupper(user2[j]);
				}
				head = remove_node(user, user2, head);
				break;
			case 'I': //print transcript
				printTranscript(head);
				break;
			case 'O': //print course from transcript
				puts("Please enter the course identifier (xx.ddd.nnn): ");
				fgets(user, 100, stdin);
				for (int i = 0; i < 100; i++) {
					user[i] = toupper(user[i]);
				}
				transCourse(user, head);
				break;
			case 'G': //calculate gpa
				calcGPA(head);
				break;
			default:
				puts("Invalid menu choice.");
				break;

		}
	}
	return 0;
}
