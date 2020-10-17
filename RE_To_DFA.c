#include <stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <string.h>


char expression[250];
int node[100][100], flps[100][100], position[100][100], DF[100][100];
int S=0, var=0, temp=1, v;

typedef struct STACK
{
    char data;
    struct STACK *next,*L,*R;
    struct STACK *D;
    int FP[100],LP[100];
}Tree;
Tree *O;
Tree *A;



void PUSHNODE(Tree *a)
{
    Tree *t;
    t=(Tree *)malloc(sizeof(Tree));
    t->D=a;
    if(O!=NULL) t->next=O;
    else        t->next=NULL;
    O=t;
}

Tree *POPNODE()
{
    Tree *t;
    t=(Tree *)malloc(sizeof(Tree));
    t=O->D;
    if(O->next!=NULL)
       {
         O=O->next;
       }
    else
        {
          O=NULL;
        }
    return t;
}


void FORMTREE(char ele[])
{
    int i,j,k;
    Tree *N;
    O=NULL;
    for(i=0;ele[i]!='\0';i++){
        N=(Tree *)malloc(sizeof(Tree));
        N->data=ele[i];
        N->L=NULL;
        N->R=NULL;
        N->next=NULL;
        N->FP[0]=0; N->LP[0]=0;
        if(ele[i]=='.'||ele[i]=='+'){
            N->R=POPNODE();
            N->L=POPNODE();
        }
        else if(ele[i]=='*'){
            N->L=POPNODE();
            N->R=NULL;
        }
        PUSHNODE(N);
    }
}
void first_pos_last_pos_display (Tree *a)
{
    int i;
    if(a!=NULL){
        first_pos_last_pos_display(a->L);
        first_pos_last_pos_display(a->R);
        S++;
        printf("\n    %c",a->data);
        printf("\t\tFIRSTPOS ->");
        for(i=1;i<=a->FP[0];i++)
            printf(" %d",a->FP[i]);
        printf("\t\tLASTPOS ->");
        for(i=1;i<=a->LP[0];i++)
            printf(" %d",a->LP[i]);
        printf("\n");

    }
}
int PRESENT(int p[], int a, int b)
{
    int i,j;
    for(i=b,j=0;j<p[b-1];i++,j++)
        if(p[i]==a)
            return 1;
    return 0;
}


void first_last_pose(Tree *a)
{
    if(a!=NULL){
        int i, flg;
        first_last_pose(a->L);
        first_last_pose(a->R);
        if(a->data!='+'&&a->data!='.'&&a->data!='*'){
            a->FP[0]++; a->LP[0]++;
            a->FP[a->FP[0]]=temp;
            a->LP[a->LP[0]]=temp++;
            flg=0;
            for(i=0;i<var;i++)
                if(position[i][0]==a->data){
                    position[i][1]++;
                    position[i][position[i][1]+1]=temp-1;
                    flg=1;
                }
            if(flg==0){
                position[var++][1]=1;
                position[var-1][2]=temp-1;
                position[var-1][0]=a->data;
            }
        }
        else if(a->data=='+'){
            for(i=1;i<=a->L->FP[0];i++){
                a->FP[0]++;
                a->FP[a->FP[0]]=a->L->FP[i];
            }
            for(i=1;i<=a->R->FP[0];i++){
                if(PRESENT(a->FP, a->R->FP[i],1)==0){
                    a->FP[0]++;
                    a->FP[a->FP[0]]=a->R->FP[i];
                }
            }
            for(i=1;i<=a->L->LP[0];i++){
                a->LP[0]++;
                a->LP[a->LP[0]]=a->L->LP[i];
            }
            for(i=1;i<=a->R->LP[0];i++)
                if(PRESENT(a->LP, a->R->LP[i], 1)==0){
                    a->LP[0]++;
                    a->LP[a->LP[0]]=a->R->LP[i];
                }
        }
        else if(a->data=='*'){
            for(i=1;i<=a->L->FP[0];i++){
                a->FP[0]++;
                a->FP[a->FP[0]]=a->L->FP[i];
            }
            for(i=1;i<=a->L->LP[0];i++){
                a->LP[0]++;
                a->LP[a->LP[0]]=a->L->LP[i];
            }
        }
        else if(a->data=='.'){
                                                                      //firstpos
            for(i=1;i<=a->L->FP[0];i++){
                a->FP[0]++;
                a->FP[a->FP[0]]=a->L->FP[i];
            }
            if(a->L->data=='*')
                for(i=1;i<=a->R->FP[0];i++)
                    if(PRESENT(a->FP, a->R->FP[i],1)==0){
                        a->FP[0]++;
                        a->FP[a->FP[0]]=a->R->FP[i];
                    }
                                                                     //lastpos
            for(i=1;i<=a->R->LP[0];i++){
                a->LP[0]++;
                a->LP[a->LP[0]]=a->R->LP[i];
            }
            if(a->R->data=='*')
                for(i=1;i<=a->L->LP[0];i++)
                    if(PRESENT(a->LP,a->L->LP[i],1)==0){
                        a->LP[0]++;
                        a->LP[a->LP[0]]=a->L->LP[i];
                    }
        }
    }
}


void Followpose_calculation(Tree *a, int n)
{
    int j;
    if(a!=NULL){
        Followpose_calculation(a->L,n);
        if(a->data=='.'){
            if(PRESENT(a->L->LP,n,1)==1)
                for(j=1;j<=a->R->FP[0];j++)
                    if(PRESENT(flps[n],a->R->FP[j],1)==0){
                        flps[n][1]++;
                        flps[n][flps[n][1]+1]=a->R->FP[j];
                    }
        }
        else if(a->data=='*'){
            if(PRESENT(a->LP,n,1)==1)
                for(j=1;j<=a->FP[0];j++)
                    if(PRESENT(flps[n],a->FP[j],1)==0){
                        flps[n][1]++;
                        flps[n][flps[n][1]+1]=a->FP[j];
                    }
        }
        Followpose_calculation(a->R,n);
    }
}

void FOLLOWPOS()
{
    int i,j,k;
    A=O;
    flps[0][0]=temp;
    for(i=1;i<=temp;i++){
        flps[i][0]=i;
        flps[i][1]=0;
        Followpose_calculation(O->D,i);
    }
    O=A;
}

void DFA()
{
    int i,j,k,l,m,fg,find;
    int tmp[10], newn[10];
    node[0][0]=1;
    node[1][0]='A';
    node[1][1]=0;
    for(i=1;i<=O->D->FP[0];i++){
        node[1][1]++;
        node[1][node[1][1]+1]=O->D->FP[i];
    }
    DF[0][0]=var-1;
    for(i=1;i<var;i++)
        DF[0][i]=position[i-1][0];
    for(i=1;i<=node[0][0];i++){
        DF[i][0]=node[i][0];
        for(j=1;j<=DF[0][0];j++){
            tmp[0]=0;
            newn[0]=0;
            for(k=2;k<=node[i][1]+1;k++){
                if(PRESENT(position[j-1],node[i][k],2)==1)
                    tmp[++tmp[0]]=node[i][k];
                for(l=1;l<=tmp[0];l++){
                    for(m=2;m<=flps[tmp[l]][1]+1;m++)
                        if(PRESENT(newn,flps[tmp[l]][m],1)==0){
                            newn[0]++;
                            newn[newn[0]]=flps[tmp[l]][m];
                        }
                }
            }
            printf(" ");
            fg=0;
            for(l=1;l<=node[0][0];l++){
                find=0;
                if(newn[0]==node[l][1])
                    for(k=1;k<=newn[0];k++)
                        if(PRESENT(node[l],newn[k],2)==0)
                            fg=1;
                        else find++;
                if(find==newn[0]&&find!=0)
                    goto l1;
            }
            if(newn[0]==0){
                DF[i][j]='-';
                goto l2;
            }
            node[0][0]++;
            node[node[0][0]][0]=node[node[0][0]-1][0]+1;
            for(m=0;m<=newn[0];m++)
                node[node[0][0]][m+1]=newn[m];
            DF[i][j]=node[node[0][0]][0];
            goto l2;
            l1:       DF[i][j]=node[l][0];
            l2:      if(fg==1||fg==0)  printf(" ");
        }
    }
    printf("\n\nNODES:\n\n");
    for(i=1;i<=node[0][0];i++,printf("\n\n"))
        for(j=0;j<=node[i][1]+1;j++)
            if(j==0)
                printf(" %c ",node[i][j]);
            else if(j==1)
                printf(" => ");
            else
                printf(" %d ",node[i][j]);
    printf("\n\nDFA TABLE:\n\n");
    for(i=0;i<=node[0][0];i++,printf("\n\n"))
        for(j=0;j<=DF[0][0];j++)
            if(i==0&&j==0)
                printf("    ");
            else
                printf("%4c",DF[i][j]);
}


void main()
{
    int i,j,k, gd, gm;
    int ch;
    O=NULL; A=NULL; v=0;
    printf("\n\n    ENTER POSTFIX REGULAR EXPRESSION : ");
    scanf("%s",&expression);
    strcat(expression,"#.\0");
    O=NULL;
    FORMTREE(expression);
    first_last_pose(O->D);
    first_pos_last_pos_display(O->D);
    FOLLOWPOS();
    printf("\n\n    FOLLOWPOS :\n\n");
    for(i=1;i<temp;i++)
    {
        for(j=0;j<=flps[i][1]+1;j++)
            if(j!=1)
                printf(" %d ",flps[i][j]);
        printf("\n");
    }


    printf("\n\n    POSITION MATRIX :\n\n");
    for(i=0;i<var;i++)
    {
        for(j=0;j<=position[i][1]+1;j++)
            if(j==0)
                printf(" %c ",position[i][j]);
            else if (j!=1)
                printf(" %d ",position[i][j]);
        printf("\n\n");
    }
    DFA();



}