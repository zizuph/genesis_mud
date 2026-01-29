
/*
 * st4.c
 * Main street of the town of haven
 * Tibbit, 4 March 1998
 *
 */

#include "../local.h"

inherit HAVENBASE;


void
create_haven()
{
    add_my_desc(
        "You are just south of the town center of Haven. Just north "+
        "of you stand the town hall and the Seekers' temple, the "+
        "largest and most important buildings in the village. "+
        "A few modest homes are south of here."+
        "\n"
        );

    add_exit(HROOM+"st3","north");
    add_exit(HROOM+"st5","south");

    add_item(({"town","city","haven"}),
        "The town of Haven is not very large, but the townspeople "+
        "seem to be doing all right for themselves.\n");
    add_item(({"street","main street"}),
        "The one major street of Haven heads north to south here.\n");
    add_item(({"hall","town hall"}),
        "Near the center of Haven "+
        "stands a simple town hall, made from unfinished wood. "+
        "It is just a bit to the north of here.\n");
    add_item(({"home","homes"}),
        "A few simple wooden homes stand along Haven's main road, "+
        "especially at the southern end of the town.\n");
    add_item(({"temple","building"}),
        "The temple of the Seekers, the religious men who handle the "+
        "affairs of this town, is the mightiest building in "+
        "Haven. Made from wood and from brick which must have been "+
        "imported from a respectable distance, the large building "+
        "is painted entirely white, and stands out as the tallest, "+
        "most noticeable thing in the town.\n");

}


