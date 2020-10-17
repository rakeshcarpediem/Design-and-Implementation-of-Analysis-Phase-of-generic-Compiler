#include<stdio.h>
#include<stdlib.h>
struct node{
    int s;
    struct node *link;
};
struct node1 {
    int n[20];
};
void insert_values(int,char,int);
int find_character(char);
void final_state(void);
int insert_dfa_state(struct node1);
void printstate(struct node1);
int comp(struct node1,struct node1);
static int s[20],state,alphabet,a,trans,final,initial,finalstate[20],b,c,d[20];
int x = -1;
char alphabets[20];
static int epsilon[20][20]={0};
int i, j, q, r, t;
struct node *z;
struct node1 nstate = {0}, tstate = {0};
struct node1 w[20];
struct  node *tr[20][20]={NULL};
void main() {
    printf("please enter the no of alphabets");
    scanf("%d", &alphabet);
    getchar();
    printf(" please note that use e letter as epsilon");
    printf("and it is also requested to use e as a last letter if present in alphabets");
    for (i = 0; i < alphabet; i++) {
        alphabets[i] = getchar();
        getchar();
    }
    printf("please enter the no of states present ");
    scanf("%d", &state);
    printf(" please enter the initial state");
    scanf("%d", &initial);
    printf("enter the no of final states");
    scanf("%d", &final);
    printf("enter the final states");
    for (i = 0; i < final;i++){
        scanf("%d", &finalstate[i]);
    }
    printf(" enter the no of transition");
    scanf("%d", &trans);
    printf("transition should be in the form of int char int means state char state");
    printf("states should be always greater than zero");
    printf("  please enter transition as per required");
    for (i = 0; i < trans; i++) {
        scanf("%d %c%d",&a,&b,&c);
        insert_values(a, b, c);

    }
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            w[i].n[j] = 0;
        }
    }
    x = -1;
    i = -1;
    printf("\n Equivalent DFA is -------\n");
    printf("--------------\n");
    nstate.n[initial] = initial;
    insert_dfa_state(nstate);
    while (i != x) {
        i++;
        nstate = w[i];
        for (q = 0; q < alphabet; q++) {
            b = 0;
            for (j = 1; j <= state; j++) {
                s[j] = 0;
            }
            for (j = 1; j <= state; j++) {
                r = nstate.n[j];
            }
            if (r != 0) {
                z = tr[r][j];
                while (z != NULL) {
                    if (s[z->s] == 0) {
                        b++;
                        s[z->s] = z->s;

                    }
                    z = z->link;
                }
            }
            printf("\n");
            if (b != 0) {
                for (t = 1; t <= state; t++) {
                    tstate.n[t] = s[t];
                }
                insert_dfa_state(tstate);
                printstate(nstate);
                printf("%c\t", alphabets[q]);
                printstate(tstate);
                printf("\n");


            } else {
                printstate(nstate);
                printf("%c\t", alphabets[q]);
                printf("NULL\n");
            }
        }


    }
    printf("\n so states of DFA:\n");
    for (i = 0; i < x; i++) {
        printstate(w[i]);
    }
    printf("so alphabets are:");
    for (i = 0; i < alphabet; i++) {
        printf("%c\t", alphabets[i]);
    }
    printf(" Initial state of DFA");
    printf("%d", initial);
    printf("final states of Dfa are:");
    final_state();
}
int insert_dfa_state(struct node1 nstate){
    int v;
    for(v=0;v<=x;v++){
        if(comp(w[v],nstate))
            return 0;

    }
    x++;
    w[x]=nstate;
    return 1;
}
int comp(struct node1 u,struct node1 v){
    int g;
    for(g=1;g<=state;g++){
        if(u.n[g]!=v.n[g])
            return 0;
    }
    return 1;

}
void insert_values(int a ,char b,int c){
    int y;
    struct node *z;
    y=find_character(b);
    if(y==-1){
        printf("ERROR ELEMENT NOT FOUND\n");
        exit(0);
    }
    z=(struct node *) malloc(sizeof(struct node));
    z->s=c;
    z->link=tr[a][y];
    tr[a][y]=z;


}
int find_character(char b){
    int e;
    for(e=0;e<alphabet;e++){
        if(alphabets[e]==b)
            return e;

    }
    return (-1);
}
void final_state(){
    int u,v,y,j;
    for(u=0;u<=x;u++){
        for(v=1;v<=state;v++){
            for(y=0;y<final;y++){
                if(w[u].n[v]==finalstate[y]){
                    printstate(w[u]);
                    v=state;
                    break;
                }
            }
        }
    }

}
void printstate(struct node1 s){
    int g;
    printf("{");
    for(g=1;g<state;g++){
        if(s.n[g]!=0)
            printf("%d",s.n[g]);
    }
    printf("}\t");
}
