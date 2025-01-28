#include <stdio.h>
#include "quadTree.h"

int main()
{
    Figure *figures[20];
    figures[0] = (Figure *)createSquare("sq1", 197, 604, 160);
    figures[1] = (Figure *)createSquare("sq2", 625.6, 436.8, 160);
    figures[2] = (Figure *)createSquare("sq3", -676.8, 401.6, 160);
    figures[3] = (Figure *)createSquare("sq4", -264, 241.6, 400);
    figures[4] = (Figure *)createSquare("sq5", 238.4, 196.8, 160);
    figures[5] = (Figure *)createSquare("sq6", 667.2, 33.6, 160);
    figures[6] = (Figure *)createSquare("sq7", -724.8, -408, 160);
    figures[7] = (Figure *)createSquare("sq8", -302.4, -568, 160);
    figures[8] = (Figure *)createSquare("sq9", 238.4, -443.2, 160);
    figures[9] = (Figure *)createSquare("sq10", 664, -600, 160);
    figures[10] = (Figure *)createSquare("sq11", 36.8, 843.2, 160);
    figures[11] = (Figure *)createSquare("sq12", 398.4, 798.4, 160);
    figures[12] = (Figure *)createSquare("sq13", 865.6, 760, 160);
    figures[13] = (Figure *)createSquare("sq14", 36.8, 456, 160);
    figures[14] = (Figure *)createSquare("sq15", 686.4, 318.4, 160);
    figures[15] = (Figure *)createSquare("sq16", 555.2, 238.4, 160);
    figures[16] = (Figure *)createCircle("cir1", -600, -56, 118.4);
    figures[17] = (Figure *)createCircle("cir2", 78.4, 120, 118.4);
    // Overlap between adjacent nodes
    figures[18] = (Figure *)createSquare("sq30", -10, 800, 160);  // Left from sq11
    figures[19] = (Figure *)createCircle("cir40", 650, 505, 100); // Above sq2

    QuadNode *root = buildTree(figures, 20);

    DynamicArray overlaps = findOverlaps(root);

    for (int i = 0; i < overlaps.size; i++)
    {
        Overlapped *over = (Overlapped *)overlaps.buffer[i];
        printf("\nOverlap between %s and %s", over->figure1->name, over->figure2->name);
    }
    releaseOverlaped(overlaps);
    releaseTree(root);
    return 0;
}
