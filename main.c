#include "stdio.h"
typedef struct {
    int a;
    int b;
} stu;
struct student {
    int c;
};
int main() 
{
    
    stu s;
    s.a=12;
    printf("%d",s.a);
    struct student s2;
    s2.c =12;
    printf("%d",s2.c);
    printf("%d",printf("123"));

}