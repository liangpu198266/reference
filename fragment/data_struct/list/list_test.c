#include <stdlib.h>
#include <malloc.h>        //malloc函数所要的头文件
#include "comm_list.h"    //链表函数多包涵的头文件
#include <memory.h>       //memset 函数所要包含的头文件

struct student  
{  
   char name[100];  
   int num;  
   struct list_head list;  
};  

struct student *pstudent;  
struct student *tmp_student;  
struct list_head student_list;  
struct list_head *pos;  

int main(void)  
{  
   int i = 0;  
   INIT_LIST_HEAD(&student_list);  
   pstudent = malloc(sizeof(struct student)*5);  
   memset(pstudent,0,sizeof(struct student)*5);  

   for(i=0;i<5;i++)
   {  
        sprintf(pstudent[i].name,"Student%d",i+1);  
        pstudent[i].num = i+1;   
        list_add( &(pstudent[i].list), &student_list);  
   }
   /*�������ǴӺ���ǰ�ı���*/
   //list_for_each(pos,&student_list) 
   list_for_each_prev(pos,&student_list)  
    {  
        tmp_student = list_entry(pos,struct student,list);  
        printf("<0>student %d name: %s\n",tmp_student->num,tmp_student->name);  
    }  
/* 实验：将for换成list_for_each来遍历删除结点，观察要发生的现象，并考虑解决办法 */
   for(i=0;i<5 ;i++)
    {  
        list_del(&(pstudent[i].list));       
    }  
    free(pstudent);  
}  
