#include <stdio.h>

struct pstruct {
    int fno;
    int pbit;
} ptable[10];

int pmsize,lmsize,psize,frame,page,ftable[20],frameno;

void info() {
    printf("MEMORY MANAGEMENT USING PAGING\n");
    printf("Enter the Size of Physical memory: ");
    scanf("%d",&pmsize);
    printf("\nEnter the size of Logical memory: ");
    scanf("%d",&lmsize);
    printf("\nEnter the partition size: ");
    scanf("%d",&psize);
    frame = (int) pmsize/psize;
    page = (int) lmsize/psize;
    printf("\nThe physical memory is divided into %d no.of frames",frame);
    printf("\nThe Logical memory is divided into %d no.of pages\n",page);
}

void assign() {
    int i;
    for (i=0;i<page;i++) {
        ptable[i].fno = -1;
        ptable[i].pbit= -1;
    }
    for(i=0; i<frame;i++)
        ftable[i] = 32555;
    for (i=0;i<page;i++) {
        printf("\nEnter the Frame number where page %d must be placed: ",i);
        scanf("%d",&frameno);
        ftable[frameno] = i;
        if(ptable[i].pbit == -1)
        {
            ptable[i].fno = frameno;
            ptable[i].pbit = 1;
        } 
    }
    // clrscr();
    printf("\nPAGE TABLE");
    printf("\nPageAddress FrameNo. PresenceBit");
    for (i=0;i<page;i++)
        printf("\n%d\t\t%d\t\t%d\n",i,ptable[i].fno,ptable[i].pbit);
    printf("\n\nFRAME TABLE\n");
    printf("FrameAddress PageNo\n");
    for(i=0;i<frame;i++)
        printf("%d\t\t%d\n",i,ftable[i]);
}

void cphyaddr() {
    int laddr,paddr,disp,phyaddr,baddr;
    // clrscr();
    printf("\nProcess to create the Physical Address\n");
    printf("\nEnter the Base Address: ");
    scanf("%d",&baddr);
    printf("\nEnter theLogical Address: ");
    scanf("%d",&laddr);
    paddr = laddr / psize;
    disp = laddr % psize;
    if(ptable[paddr].pbit == 1 )
        phyaddr = baddr + (ptable[paddr].fno*psize) + disp;
    printf("\nThe Physical Address where the instruction present: %d",phyaddr);
}

int main() {
    info();
    assign();
    cphyaddr();
}

/* Expected output

MEMORY MANAGEMENT USING PAGING

Enter the Size of Physical memory: 4

Enter the size of Logical memory: 4

Enter the partition size: 2

The physical memory is divided into 2 no.of frames
The Logical memory is divided into 2 no.of pages

Enter the Frame number where page 0 must be placed: 1

Enter the Frame number where page 1 must be placed: 2

PAGE TABLE
PageAddress FrameNo. PresenceBit
0		1		1

1		2		1


FRAME TABLE
FrameAddress PageNo
0		32555
1		0

Process to create the Physical Address

Enter the Base Address: 3

Enter theLogical Address: 4

The Physical Address where the instruction present: 10059780
*/
