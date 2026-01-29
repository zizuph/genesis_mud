
/* square_se.c
 * Town of Gamwich
 * Town Square
 * SE corner
 * Created 23 February 1995 by Farlong
 */

inherit "/d/Shire/eastroad/eroad";

#include "defs.h"

void
create_room()
{
    area="in";
    areaname="the village of Gamwich";
    land="the West Farthing of the Shire";
    areatype=10;
    areadesc="town square";
    grass="wild";

    extraline="This is the southeastern corner of the "+
        "town square of the tiny hobbit-village of Gamwich.  The square "+
        "continues to the north and west, while a well-kept "+
        "dirt path heads southeastward out of town.  Off to the "+
        "east stands a field of wild grasses.";

    add_item(({"square","town square"}),"The town square is a "+
        "large, well-kept space at the center of "+
        "Gamwich.  Paths of dirt "+
        "head out from each of its four corners.\n");
    add_item(({"path","paths","road","roads","dirt path",
        "dirt paths","dirt road","dirt roads"}),
        "A dirt path heads out of each of the four corners of "+
        "the central square of Gamwich.  The closest path heads "+
        "southeast, leaving the town and heading out towards "+
        "the hamlet of Tighfield."+
        "\n");
    add_item(({"field","grass","grasses","wild grass","wild grasses"}),
        "A field of wild grasses extends to the east here, just "+
        "outside the town of Gamwich.  The grass is a type common "+
        "to this part of the Shire.\n");

    add_exit(GAMWICH_DIR+"road_start","southeast");
    add_exit(GAMWICH_DIR+"square_ne","north");
    add_exit(GAMWICH_DIR+"square_sw","west");

    make_the_room();

}

