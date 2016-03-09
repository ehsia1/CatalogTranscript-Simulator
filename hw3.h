/* Evan Hsia, ehsia1, Homework 3 function headers */


struct courseID {
        char division[3];
        int courseDep;
        int courseNum;
        float credit;
        char title[33];
};

struct node {
        struct courseID student;
        char term[7];
        char grade[3];
        struct node *next;
};
//catalog functions
void printCatalog(struct courseID *course, int lines);
void specCourse(struct courseID *course, int lines, char user[]);
void newTitle(struct courseID *course, int lines, char user[], char user2[], struct node *head);
void newCredit(struct courseID *course, int lines, char user[], char user2[], struct node *head);

//transcript functions
struct node *new_node(char id[], char term[], struct courseID *course, int lines, struct node *cur);
struct node *remove_node(char user[], char user2[], struct node *cur);
struct node *reorderList(struct node *cur);
void printTranscript(struct node *head);
void transCourse(char user[], struct node *cur);
void calcGPA(struct node *cur);
