#include<stdio.h>
#include<stdlib.h>

struct list {
    int seg;
    int base;
    int limit;
    struct list *next;
} *p;

void insert(struct list *q,int base,int limit,int seg) {
    if(p==NULL) {
        p=malloc(sizeof(struct list));
        p->limit=limit;
        p->base=base;
        p->seg=seg;
        p->next=NULL;
    } else {
        while(q->next!=NULL) {
            q=q->next;
            printf("yes\n");
        }
        q->next=malloc(sizeof(struct list));
        q->next ->limit=limit;
        q->next ->base=base;
        q->next ->seg=seg;
        q->next ->next=NULL;
    }
}

int find(struct list *q,int seg) {
    while(q->seg!=seg) {
        q=q->next;
    }
    return q->limit;
}

int search(struct list *q,int seg) {
    while(q->seg!=seg) {
        q=q->next;
    }
    return q->base;
}

int main() {
    p=NULL;
    int seg,offset,limit,base,c,s,physical;
    printf("Enter segment table:\n");
    printf("Enter -1 as segment value for termination:\n");

    do {
        printf("Enter segment number: ");
        scanf("%d",&seg);
        if(seg!=-1) {
            printf("\nEnter base value: ");
            scanf("%d",&base);
            printf("\nEnter value for limit: ");
            scanf("%d",&limit);
            insert(p,base,limit,seg);
        }
    }
    while(seg!=-1);

    printf("\nEnter offset: ");
    scanf("%d",&offset);
    printf("\nEnter bsegmentation number: ");
    scanf("%d",&seg);
    c=find(p,seg);
    s=search(p,seg);
    if(offset<c) {
        physical=s+offset;
        printf("\nAddress in physical memory %d\n",physical);
    } else {
        printf("error");
    }
}

/* Expected Output

Enter segment table:
Enter -1 as segment value for termination:
Enter segment number: 1

Enter base value: 2000

Enter value for limit: 100
Enter segment number: 2

Enter base value: 2500

Enter value for limit: 100
Enter segment number: -1

Enter offset: 90

Enter bsegmentation number: 2

Address in physical memory 2590

*/
