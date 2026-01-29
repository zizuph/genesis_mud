
/*
 * st2.c
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
        "The main street of the town of Haven extends here from "+
        "north to south, passing through the center of town. "+
        "One of the simple homes of the residents of Haven lies "+
        "just west of here. You note a local vegetable merchant's "+
        "stand at the east side of the street. Just south of here, "+
        "this road passes between the simple town hall and the "+
        "large Seekers' temple."+
        "\n"
        );

    add_exit(HROOM+"st1","north");
    add_exit(HROOM+"st3","south");
    add_exit(HROOM+"home3","west");
    add_exit(HROOM+"veg_mer","east");

    add_item(({"town","city","haven"}),
        "The town of Haven is not very large, but the townspeople "+
        "seem to be doing all right for themselves.\n");
    add_item(({"street","main street"}),
        "The one major street of Haven heads north to south here.\n");
    add_item(({"hall","town hall"}),
        "Near the center of Haven, south of your current position, "+
        "stands a simple town hall, made from unfinished wood.\n");
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


