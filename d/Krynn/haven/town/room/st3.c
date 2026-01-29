
/*
 * st3.c
 * Main street of the town of haven
 * Tibbit, 4 March 1998
 *
 */

#include "../local.h"

inherit HAVENBASE;

object citizen1,seeker;

void
reset_haven()
{
    reset_euid();

    if(!citizen1)
        (citizen1 = clone_object(HNPC+"citizen_"+
            (random(2)?"m":"f")))->move(TO);

    if((!seeker) && (!random(3)))
        (seeker = clone_object(HNPC+"seeker"))->move(TO);
}

void
create_haven()
{
    add_my_desc(
        "This is the center of the town of Haven, a simple but "+
        "prosperous community. You stand on the main street, "+
        "which heads north out of town and south toward "+
        "more houses. The wooden town hall is just west of here. "+
        "Stepping to the east, you may enter the gleaming white "+
        "temple of the Seekers."+
        "\n"
        );

    add_exit(HROOM+"st2","north");
    add_exit(HROOM+"st4","south");
    add_exit(HROOM+"hall","west");
    add_exit(HROOM+"vestibule","east");

    add_item(({"town","city","haven"}),
        "The town of Haven is not very large, but the townspeople "+
        "seem to be doing all right for themselves.\n");
    add_item(({"street","main street"}),
        "The one major street of Haven heads north to south here.\n");
    add_item(({"hall","town hall"}),
        "Near the center of Haven "+
        "stands a simple town hall, made from unfinished wood. "+
        "It is just west of here.\n");
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


