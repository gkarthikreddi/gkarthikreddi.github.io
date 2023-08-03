#include<stdio.h>

int main() {
    int m[48], b[10][2], n,i,j,ch,k;
    int f[10];
    printf("enter the number of blocks available: \n");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        m[i]=0;
    }
    i=0;

    do {
        printf("enter name of file:\n");
        scanf("%d", &f[i]);
        printf("enter starting block and length: \n");
        scanf("%d%d",&b[i][0], &b[i][1]);
        for(j=b[i][0];j<(b[i][0]+b[i][1]);j++) {
            if(m[j]==0) {
                printf(".....allocating.....\n");
                m[j]=f[i];
            }else {
                printf("allocation is not possible\n");
                k=j;
                for(j=b[i][0];j<=k;j++)
                    m[j]=0;
                i--;
                break;
            } 
        }
        printf("Is ther any another file to be allocated(1/0):\n");
        scanf("%d", &ch);
        i++;
    } while(ch==1);

    printf("\t file allocation table\n");
    printf("file name starting block length\n");
    for(j=0;j<i;j++) {
        printf("%d\t%d\t%d\t",f[j],b[j][0],b[j][1]);
        printf("\n");
    }
}

/* Expected output

enter the number of blocks available:
32
enter name of file:
1
enter starting block and length:
2
3
.....allocating.....
.....allocating.....
.....allocating.....
Is ther any another file to be allocated(1/0):
0
	 file allocation table
file name starting block length
1	2	3

*/
