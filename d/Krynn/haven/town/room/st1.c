
/*
 * st1.c
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
        "You stand at the northern edge of the town of Haven. "+
        "Although spoken of as the capital of Abanasinia, Haven "+
        "is not as large as many cities. The town's main street "+
        "leads southward from here, passing by a town hall, a few "+
        "simple homes, and the town's largest building, the "+
        "recently-built temple of the Seekers."+
        "\n"
        );

    add_exit(HROOM+"entrance","west");
    add_exit(HROOM+"st2","south");

    add_item(({"town","city","haven"}),
        "The town of Haven is not very large, but the townspeople "+
        "seem to be doing all right for themselves.\n");
    add_item(({"street","main street"}),
        "The one major street of Haven heads south from here.\n");
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


