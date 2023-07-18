#include<stdio.h>

int i,j,nof,nor,flag=0,ref[50],frm[50],pf=0,victim=-1;

int main() {
    printf("FIFO PAGE REPLACEMENT ALGORITHM");
    printf("\nEnter no.of frames: ");
    scanf("%d",&nof);
    printf("Enter number of reference string: ");
    scanf("%d",&nor);
    printf("Enter the reference string: ");
    for(i=0;i<nor;i++)
        scanf("%d",&ref[i]);
    printf("\nThe given reference string: ");
    for(i=0;i<nor;i++)
        printf("%4d",ref[i]);
    for(i=1;i<=nof;i++)
        frm[i]=-1;
    printf("\n");
    for(i=0;i<nor;i++) {
        flag=0;
        printf("\nReference np%d->\t",ref[i]);
        for(j=0;j<nof;j++) {
            if(frm[j]==ref[i]) {
                flag=1;
                break;
            }
        }
        if(flag==0) {
            pf++;
            victim++;
            victim=victim%nof;
            frm[victim]=ref[i];
            for(j=0;j<nof;j++)
                printf("%4d",frm[j]);
        }
    }
    printf("\nNo.of pages faults...%d",pf);
}

/* Expected Output 
 
FIFO PAGE REPLACEMENT ALGORITHM
Enter no.of frames: 4
Enter number of reference string: 6
Enter the reference string: 1 2 3 4 6 7

The given reference string:    1   2   3   4   6   7

Reference np1->	   1  -1  -1  -1
Reference np2->	   1   2  -1  -1
Reference np3->	   1   2   3  -1
Reference np4->	   1   2   3   4
Reference np6->	   6   2   3   4
Reference np7->	   6   7   3   4
No.of pages faults...6%

*/
