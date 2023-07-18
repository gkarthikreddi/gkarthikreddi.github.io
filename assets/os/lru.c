#include <stdio.h>

int i,j,nof,nor,flag=0,ref[50],frm[50],pf=0,victim=-1;

int recent[10],lrucal[50],count=0;

int lruvictim();

int main() {
    printf("LRU PAGE REPLACEMENT ALGORITHM");
    printf("\nEnter no.of Frames....");
    scanf("%d",&nof);
    printf("\nEnter no.of reference string..");
    scanf("%d",&nor);
    printf("\nEnter reference string..");
    for(i=0;i<nor;i++)
        scanf("%d",&ref[i]);
    printf("\nLRU PAGE REPLACEMENT ALGORITHM ");
    printf("\nThe given reference string:");
    printf("\n………………………………..");
    for(i=0;i<nor;i++)
        printf("%4d",ref[i]);
    for(i=1;i<=nof;i++) {
        frm[i]=-1;
        lrucal[i]=0;
    }
    for(i=0;i<10;i++)
        recent[i]=0;
    printf("\n");
    for(i=0;i<nor;i++) {
        flag=0;
        printf("\nReference NO %d->\t",ref[i]);
        for(j=0;j<nof;j++) {

            if(frm[j]==ref[i]) {
                flag=1;
                break;
            }
        }
        if(flag==0) {
            count++;
            if(count<=nof)
                victim++;
            else
                victim=lruvictim();
            pf++;
            frm[victim]=ref[i];
            for(j=0;j<nof;j++)
                printf("%4d",frm[j]);
        }
        recent[ref[i]]=i;
    }
    printf("\n\nNo.of page faults...%d",pf);
}

int lruvictim() {
    int i,j,temp1,temp2;
    for(i=0;i<nof;i++) {
        temp1=frm[i];
        lrucal[i]=recent[temp1];
    }
    temp2=lrucal[0];
    for(j=1;j<nof;j++) {
        if(temp2>lrucal[j])
            temp2=lrucal[j];
    }
    for(i=0;i<nof;i++)
        if(ref[temp2]==frm[i])
            return i;
    return 0;
}

/* Expected output 

LRU PAGE REPLACEMENT ALGORITHM
Enter no.of Frames....3

Enter no.of reference string..6

Enter reference string..4 7 6 1 8 3 2 9

LRU PAGE REPLACEMENT ALGORITHM
The given reference string:
………………………………..   4   7   6   1   8   3

Reference NO 4->	   4  -1  -1
Reference NO 7->	   4   7  -1
Reference NO 6->	   4   7   6
Reference NO 1->	   1   7   6
Reference NO 8->	   1   8   6
Reference NO 3->	   1   8   3

No.of page faults...6%
*/
