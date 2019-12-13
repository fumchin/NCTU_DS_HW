#include <stdio.h>

typedef  struct node
{
    void *dataPtr1;
    void *dataPtr2;
    struct node* link;
}Node;

struct student{
    int id;
    float grade_point_average;
};

int main()
{
    printf("Hello World!\n");
    return 0;
}
