#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student_struct
{
    char name[16];
    int age;
    float gpa;
    struct student_struct *next;
} Student;

Student head; //The head of the linked list

/* Given the student values, initialize a structure,
   and return a pointer to the struct */
Student *makeStudent(char name[16], int age, double gpa)
{
    Student *s = (Student *)malloc(sizeof(Student));//allocates memory
    strcpy(s->name, name);
    s->gpa = gpa;
    s->age = age;
    return s; 
}


/* Inserts an element to the front of the linkedList */
void push(Student *student)
{
    if(head.next == NULL){//if the dummy head points to nothing
        head.next = student;
    }else{
        student->next = head.next;//dummy head now points to student
        head.next = student;
    }
    
 }
    
void printList()//used for debugging
{
    Student * curr = head.next;
    
    while(curr != NULL)
    {
        printf("%s:%f", curr->name, curr->gpa);
        curr = curr->next;
    }
}


/* Traverses the linked list and returns the student with the best GPA */
Student *findTopStudent()
{
    
    Student *current = head.next;
    Student *top = current;
    float max = 0;
    
    while(current != NULL){//goes through linked list and compares each node with the node with the highest gpa so far
        if(current->gpa > top->gpa){
            //printf("%s:%f is bigger than %s:%f\n", current->name, current->gpa, top->name, top->gpa);
        max = current->gpa;
        top = current;
         }
         current = current->next;
    }
    return top;  
}

/* Traverses the linked list and returns the average GPA across all students */
float getAverageGPA()
{
    
    Student *current = head.next;
    float ave = 0;
    int count = 0;
    
    while(current != NULL){//adds each gpa from the linked list
        ave += current->gpa;
        current = current->next;
        count++;
    }
   
    return (ave/count);  
}

int main(int argc, char **argv)
{
    if(argc != 2){
        perror("ERROR: Wrong number of command line args!\n");
        return -1;
    }

    head.next = NULL; 
    FILE * file;
    file = fopen(argv[1] , "r");
    if (!file){
        perror("ERROR opening file!\n");
        return -1;
    }

  

    char s1[16];
    char s2[16];
    char s3[16];

    while (fscanf(file, "%s %s %s", s1,s2,s3)!=EOF)
    {
        printf("READING FILE LINE: %s %s %s\n",s1, s2, s3);
        push(makeStudent(s1, atoi(s2), atof(s3)));//creates students and pushes them to top of list
    }
    fclose(file);

    
    Student *topStudent = findTopStudent();
    printf("The Student with the best GPA is: %s\n", topStudent->name);
    printf("The average GPA is: %.2f\n", getAverageGPA());

    return 0;
}