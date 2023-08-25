#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct date
{
    int d,m,y;
};
struct student
{
    int test;
    int num;
    int n_b_s;
    char name[30];
    int pun;
    struct date doh;
};
struct writer
{
    char name_w[30];
};
struct book
{
    int test;
    int isbn;
    char title[30];
    int n_b;
    struct writer w[5];
    char section[30];
    int nob;
    int no_borrow;
};
struct borrow
{
    struct book b;
    struct student s;
    struct date dob;
    struct date doc;
    int test;
};
void deleate_b(char *name);
void deleat_s(char *name);
struct book search_b (char *name);
struct student search_s(char *name);
void add_borrow(struct student s,struct book b);
void open_s(struct student s);
void open_b(struct book b);
void add_b(char *name);
void display ();
void display_one_book(struct book b);
void display_one_book(struct book b)
{
    int i;
    printf("*******************************************************\n\n");
    printf("   name  \t  isbn  \t  section \t  nob  \t           writers  \n");
    printf("%8s  \t  %3d  \t",b.title,b.isbn);
    printf("     %10s  \t  %3d  \t",b.section,b.nob);
    for(i=0; i<b.n_b; i++)
    {
        printf("\t%8s  \n\t\t\t\t\t\t\t",b.w[i].name_w);
    }
    printf("\n");
    printf("********************************************************\n");
}
void deleate_b(char *name)
{
    FILE *f,*ft;
    f=fopen("file1.bin","rb");
    ft=fopen("temp.bin","wb");
    if(f==NULL||ft==NULL)
    {
        printf("error12\n");
        exit(-1);
    }
    struct book test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(strcmp(name,test.title)==0)
        {
            continue;
        }
        else
            fwrite(&test,sizeof(test),1,ft);
    }
    fclose(f);
    fclose(ft);
    f=fopen("file1.bin","wb");
    ft=fopen("temp.bin","rb");
    while((fread(&test,sizeof(test),1,ft))!=NULL)
    {
        fwrite(&test,sizeof(test),1,f);
    }
    fclose(f);
    fclose(ft);
}
void deleat_s(char *name)
{
    FILE *f=fopen("file2.bin","rb");
    FILE *ft=fopen("temp1.bin","wb");
    if (f==NULL||ft==NULL)
    {
        printf("error13\n");
        exit(-1);
    }
    struct student test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if (strcmp(name,test.name)==0)
            continue;
        else
            fwrite(&test,sizeof(test),1,ft);
    }
    fclose(f);
    fclose(ft);
    f=fopen("file2.bin","wb");
    ft=fopen("temp1.bin","rb");
    while((fread(&test,sizeof(test),1,ft))!=NULL)
    {
        fwrite(&test,sizeof(test),1,f);
    }
    fclose(f);
    fclose(ft);
}
struct book search_b (char *name)
{
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error7\n");
        exit(-1);
    }
    struct book test;
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        if((strcmp(name,test.title))==0)
        {
            test.test=1;
            fclose(f);
            return test;
        }
    }
    fclose(f);
    test.test=0;
    test.nob=0;
    return test;
}
int search_s_n(int n)
{
    FILE *f=fopen("file2.bin","rb");
    if(f==NULL)
    {
        printf("error6\n");
        exit(-1);
    }
    struct student test;
    while (fread(&test,sizeof(test),1,f)!=NULL)
    {
        if(test.num==n)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
struct student search_s(char *name)
{
    FILE *f=fopen("file2.bin","rb");
    if(f==NULL)
    {
        printf("error6\n");
        exit(-1);
    }
    struct student test;
    while (fread(&test,sizeof(test),1,f)!=NULL)
    {
        if(strcmp(test.name,name)==0)
        {
            fclose(f);
            test.test=1;
            return test;
        }
    }
    fclose(f);
    test.test=0;
    test.pun=0;
    test.n_b_s=0;
    return test;
}
void open_borrow( struct borrow b)
{
    FILE *f=fopen("file3.bin","ab");
    if(f==NULL)
    {
        printf("error 15");
        exit(-1);
    }
    fwrite(&b,sizeof(b),1,f);
    fclose(f);
}
void add_borrow(struct student s,struct book b)
{
    if(b.nob==0)
    {
        printf("**borrow cant be successful**\n\n**book is finished**\n\n");
        return;
    }
    s.n_b_s=s.n_b_s+1;
    if(s.n_b_s>3)
    {
        printf("borrow cant be succeed\n");
        return;
    }
    struct borrow borrow;
    b.nob=b.nob-1;
    b.no_borrow=b.no_borrow+1;
    borrow.b=b;
    if(b.nob==0)
    {
        printf("this book is finished\n");
        deleate_b(b.title);
        open_b(b);
    }
    else
    {
        deleate_b(b.title);
        open_b(b);
    }
    borrow.s=s;
    deleat_s(s.name);
    open_s(s);
    printf("enter the date of taking the book like day/month/year:");
    scanf("%d/%d/%d",&borrow.dob.d,&borrow.dob.m,&borrow.dob.y);
    if(s.pun==1)
    {
        struct date test;
        test=s.doh;
        test.m=test.m+1;
        if(test.m>12)
        {
            test.y=test.y+1;
            test.m=1;
        }
        if(compare_date(test,borrow.dob)==1)
        {
            printf("\n\n**********this student is punished*************\n\n");
            return;
        }
    }
error:
    printf("enter the date which the book should be back at him like day/month/year:");
    scanf("%d/%d/%d",&borrow.doc.d,&borrow.doc.m,&borrow.doc.y);
    while(compare_date(borrow.dob,borrow.doc)!=-1)
    {
        printf("\n\n***you entered a wrong date***\n");
        goto error;
    }
    printf("borrow is successful\n");
    printf("\n\n***********%d*********\n\n",s.n_b_s);
    open_borrow(borrow);
    display_borrow(borrow);
    return;

}
void open_s(struct  student s)
{
    FILE *f=fopen("file2.bin","ab");
    if (f==NULL)
    {
        printf("error5\n");
        exit(-1);
    }
    fwrite(&s,sizeof(s),1,f);
    fclose(f);
}
void open_b(struct book b)
{
    FILE *f1=fopen("file1.bin","ab");
    if(f1==NULL)
    {
        printf("error4\n");
        exit(-1);
    }
    fwrite(&b,sizeof(b),1,f1);
    fclose(f1);
}
void add_b(char *name)
{
    struct book b;
    int choice;
    b.test=0;//not found ::::
    b=search_b(name);
    if(b.test==0) //book not exist
    {
        strcpy(b.title,name);
        printf("enter the number of book (isbn):");
        scanf("%d",&b.isbn);
        while(b.isbn<=0)
        {
            printf("error3 \n please enter a positive number :");
            scanf("%d",&b.isbn);
        }
        printf("enter the number of writers :");
        int i;
        scanf("%d",&b.n_b);
        while(1>b.n_b||b.n_b>10)
        {
            printf("\nenter number between 1&&10");
            scanf("%d",&b.n_b);
        }
        for(i=0; i<b.n_b; i++)
        {
            printf("enter the name of writer(%d):",i+1);
            fflush(stdin);
            gets(b.w[i].name_w);
        }
        printf("enter the name of section :");
        fflush(stdin);
        gets(b.section);
        printf("enter the number of books :");
        scanf("%d",&b.nob);
        while(b.nob<=0)
        {
            printf("error 1\n please enter a positive number :");
            scanf("%d",&b.nob);
        }
        b.no_borrow=0;
        open_b(b);
        return ;
    }
    else
    {
        int test;
        printf("**this book is found** \n");
error:
        printf("press (1)...for input copies for this book\npress(2)...for back to the main menu\nwhat is your choice:");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("enter the numbers for this book:");
            scanf("%d",&test);
            b.nob=b.nob+test;
            deleate_b(b.title);
            open_b(b);
        }
        else if(choice==2)
            return ;
        else
        {
            printf("\n**enter number from list **\n");
            goto error;
        }
    }
}
void display ()
{
    struct book test;
    int i;
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error 10\n");
        exit(-1);
    }
    printf("***********************************************************************************\n\n");
    printf("   name  \t  isbn  \t  section  \t  nob  \t           writers  \n");
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(test.nob==0)
            return;
        printf("%8s  \t  %3d  \t",test.title,test.isbn);
        printf("     %10s  \t  %3d  \t",test.section,test.nob);
        for(i=0; i<test.n_b; i++)
        {
            printf("\t%8s  \n\t\t\t\t\t\t\t",test.w[i].name_w);
        }
        printf("\n");

    }
    fclose(f);
    printf("***********************************************************************************\n");
}
void search_w(char *name_w)
{
    int test1=0,i;
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error12");
        exit(-1);
    }
    struct book test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        for (i=0; i<test.n_b; i++)
            if((strcmp(name_w,test.w[i].name_w))==0)
            {
                display_one_book(test);
                test1=1;
            }
    }
    if(test1==0)
        printf("\n********not found by the name of writer**********\n\n");
    fclose(f);
}
int compare_date (struct date a,struct date b)
{
    if(a.y==b.y&&a.m==b.m&&a.d==b.d)
        return 0;
    if(a.y==b.y)
        if(a.m>b.m)
            return 1;
        else if(a.m<b.m)
            return -1;
        else if(a.m==b.m)
            if(a.d>b.d)
                return 1;
            else
                return -1;
    if(a.y>b.y)
        return 1;
    else
        return -1;

}
struct borrow search_borrow(char *name_s,char *name_b)
{
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
    {
        printf("error 14\n");
        exit(-1);
    }
    struct borrow test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(strcmp(name_s,test.s.name)==0&&strcmp(name_b,test.b.title)==0)
        {
            fclose(f);
            return test;
        }
    }
    fclose(f);
    test.test=0;
    return test;//not found
}
void open_re(struct book b)
{
    FILE *f=fopen("temp4.bin","ab");
    if(f==NULL)
    {
        printf("error19\n");
        exit(-1);
    }
    fwrite(&b,sizeof(b),1,f);
    fclose(f);
}
void re_back (struct borrow b)
{
    b.b.nob=b.b.nob+1;
    b.s.n_b_s=b.s.n_b_s-1;
    deleate_b(b.b.title);
    open_b(b.b);
    struct date test;
    printf("enter the date of re_back book like day/month/years:");
    scanf("%d/%d/%d",&test.d,&test.m,&test.y);
    if((compare_date(b.doc,test))==-1)
    {
        b.s.pun=1;
        b.s.doh=test;
        deleat_s(b.s.name);
        open_s(b.s);
        open_re(b.b);
    }
    else
    {
        deleat_s(b.s.name);
        open_s(b.s);
    }
    deleate_borrow(b);
}
void deleate_borrow(struct borrow b)
{
    FILE *f,*ft;
    f=fopen("file3.bin","rb");
    ft=fopen("temp2.bin","wb");
    if(f==NULL||ft==NULL)
    {
        printf("error12\n");
        exit(-1);
    }
    struct borrow test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(strcmp(b.b.title,test.b.title)==0)
        {
            continue;
        }
        else
            fwrite(&test,sizeof(test),1,ft);
    }
    fclose(f);
    fclose(ft);
    f=fopen("file3.bin","wb");
    ft=fopen("temp2.bin","rb");
    while((fread(&test,sizeof(test),1,ft))!=NULL)
    {
        fwrite(&test,sizeof(test),1,f);
    }
    fclose(f);
    fclose(ft);
}
void search_s_b(char *name_s)
{
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
    {
        printf("error16");
        exit(-1);
    }
    struct borrow borow;
    int test=0;
    int i=1;
    printf("****************\nbook list:\n");
    while((fread(&borow,sizeof(borow),1,f))!=NULL)
    {
        if(strcmp(name_s,borow.s.name)==0)
        {
            printf("(%d)...%s\n",i++,borow.b.title);
            test=1;
        }

    }
    printf("************************");
    if(test==0)
        printf("\n\n*************that student not found***************\n\n");
}
void display_borrow(struct borrow b)
{
    printf("\n*************************************************\n");
    printf("book name  \t  student     \t  date of borrowing\n");
    printf("***************************************************\n");
    printf("%s    \t  %s        \t  %d/%d/%d\n",b.b.title,b.s.name,b.dob.d,b.dob.m,b.dob.y);
    printf("***************************************************\n");
}

void sort_by_array(struct borrow test[],int n)
{
    if(n==1)
        return;
    int i;
    for(i=0; i<n; i++)
    {
        if(compare_date(test[i].dob,test[i+1].dob)==-1)
        {
            struct borrow temp;
            temp=test[i];
            test[i]=test[i+1];
            test[i+1]=temp;

        }

    }
    return sort_by_array(test,n-1);
}
void sort_by_ne_borrow(struct book test[],int n)
{

        if(n==1)
            return;
        int i,j;
        for(i=0; i<n-1; i++)
            for(j=i;j<n;j++)
        {
            if(test[i].no_borrow<test[j].no_borrow)
            {
                struct book temp;
                temp=test[i];
                test[i]=test[j];
                test[j]=temp;

            }
    }
}
void sort_by_date(int x)
{
    int n=0;
    struct borrow finals[120];
    struct borrow test;
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
    {
        printf("error 18\n");
        exit(-1);
    }
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        finals[n]=test;
        n++;
    }
    fclose(f);
    sort_by_array(finals,n);
    int i;
    for (i=0; i<n; i++)
    {if(finals[i].dob.m==x)
        display_borrow(finals[i]);
    }
}
void display_re( struct book test)
{
    int i;
    printf("*******************************************************\n\n");
    printf("   name  \t  isbn  \t  section  \t           writers  \n");
    printf("%8s  \t  %3d  \t",test.title,test.isbn);
    printf("     %10s    \t",test.section,test.nob);
    printf("%d",test.no_borrow);
    for(i=0; i<test.n_b; i++)
    {
        printf("\t%8s  \n\t\t\t\t\t\t",test.w[i].name_w);
    }
    printf("\n********************************************************\n");
}

void sort_by_noborrow()
{

   FILE*f=fopen("file1.bin","rb");
   if(f==NULL)
   {
       printf("error19\n");
       exit(-1);
   }
   int i=0;
   struct book test,finals[20];
   while(fread(&test,sizeof(test),1,f)!=NULL)
   {
       finals[i]=test;
       i++;
   }
   fclose(f);
   int j;
   sort_by_ne_borrow(finals,i);
   for(j=0;j<i;j++)
   {
       display_re(finals[j]);
   }
}
void dsiplay_book_should_back(struct book b)
{
     int i;
    printf("*******************************************************\n\n");
    printf("   name  \t  isbn  \t  section  \t  nob  \t           writers  \n");
    printf("%8s  \t  %3d  \t",b.title,b.isbn);
    printf("     %10s  \t  %3d  \t",b.section,b.nob);
    for(i=0; i<b.n_b; i++)
    {
        printf("\t%8s  \n\t\t\t\t\t\t\t",b.w[i].name_w);
    }
    printf("\n");

}

    int main()
    {printf("\n\t\t\t\t\t\t\t\t\t\t\t\t welcome to the library\n\n");
        int choise;
        while (choise!=11)
        {
            printf("(1)..input a new book to library\n");
            printf("(2)..input a borrows data\n");
            printf("(3)..re_back a book\n");
            printf("(4)..display data of library\n");
            printf("(5)..search on book by name\n");
            printf("(6)..display all book for the same writer\n");
            printf("(7)..display all borrows book from the same student\n");
            printf("(8)..display borrow process by 1 month sort by date\n");
            printf("(9)..display book sort by the mostly borrow\n");
            printf("(10)..display book which should be back and don't re_back\n");
            printf("(11)..***********EXIT**********\n");
            printf("the choice:");
            scanf("%d",&choise);
            switch(choise)
            {
            case 1:
            {
                char name[30];
                printf("enter the name of book:");
                fflush(stdin);
                gets(name);
                add_b(name);
                break;
            }
            case 2:
            {
                char name_b[30];
                char name_s[30];
                printf("enter the name of book:");
                fflush(stdin);
                gets(name_b);
                struct book b;
                b.test=0;
                b=search_b(name_b);
                if(b.test==0)
                {
                    printf("\n\n**this book is not found**\n\n");
                    break;
                }
                printf("enter the name of student:");
                fflush(stdin);
                gets(name_s);
                struct student s;
                s.test=0;
                s=search_s(name_s);
                if(s.test==0)
                {
                    strcpy(s.name,name_s);
                    printf("enter the (id) of student:");
                    scanf("%d",&s.num);
                    while(search_s_n(s.num)==1)
                    {
                        printf("this (id) is found\nenter new id\n");
                        scanf("%d",&s.num);
                    }
                    s.pun=0;
                    s.n_b_s=0;
                    open_s(s);
                }
                struct borrow test;
                test.test=0;
                test=search_borrow(s.name,b.title);
                if(test.test==0)
                    add_borrow(s,b);
                else
                {
                    printf("\n\n***this student has this book**\n\n{{{borrow cant be succesful}}}\n");
                    break ;
                }
                break;
            }
            case 3:
            {
                char name_s[30],name_b[30];
                printf("enter the name of book:");
                fflush(stdin);
                gets(name_b);
                printf("enter the name of student:");
                fflush(stdin);
                gets(name_s);
                struct borrow borow;
                borow=search_borrow(name_s,name_b);
                if(borow.test==0)
                {
                    printf("\n\n****borrows data not found*****\n\n");
                    break;
                }
                re_back(borow);
                break;
            }
            case 4:
            {

                display();
                break;
            }
            case 5:
            {
                char name_b[30];
                printf("enter the name of book to search on him:");
                fflush(stdin);
                gets(name_b);
                struct book test;
                test.test=0;
                test=search_b(name_b);
                if(test.test==0)
                {
                    printf("\n\n***********this book not found*********\n\n\n");
                    break;
                }
                else
                {
                    display_one_book(test);
                    break;

                }
            }
            case 6:
            {
                char name_w[30];
                printf("enter the name of the writer:");
                fflush(stdin);
                gets(name_w);
                search_w(name_w);
                break;
            }
            case 7:
            {
                char name_s[30];
                printf("enter the name of student:");
                fflush(stdin);
                gets(name_s);
                search_s_b(name_s);
                break;
            }
            case 8:
            {
                int n;
                 printf("enter the number of month which you wont to see the borrow process at him:");
                 scanf("%d",&n);
                sort_by_date(n);
                break;
            }
            case 9:
            {
                sort_by_noborrow();
                break;
            }
            case 10:
            {
                 FILE *f3=fopen("temp4.bin","rb");
                 if(f3==NULL)
                 {
                     printf("error20\n");
                     exit(-1);
                 }
                 struct book test;
                 while(fread(&test,sizeof(test),1,f3)!=NULL)
                 {
                     dsiplay_book_should_back(test);
                 }
                 fclose(f3);
                break;
            }
            default:
            {
                printf("*************enter number between 1&&10************\n");
                break;
            }
            }
        }
        return 0;
    }

