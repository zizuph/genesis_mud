
/* square_sw.c
 * Town of Gamwich
 * Town Square
 * SW corner
 * Created 23 February 1995 by Farlong
 */

inherit "/d/Shire/eastroad/eroad";

#include "defs.h"

object hobbit;

void
reset_room()
{
    if(!hobbit)
    {
        hobbit=clone_object(ER_DIR+"npc/femhobbit");
        hobbit->arm_me();
        hobbit->move(TO);
    }
}

void
create_room()
{
    area="in";
    areaname="the village of Gamwich";
    land="the West Farthing of the Shire";
    areatype=10;
    areadesc="the town square";
    grass="dead";

    extraline="You stroll through the town square of the "+
        "hobbit-village of Gamwich.  This tiny hamlet is "+
        "quite homely. A path leads southwest from here; "+
        "there is also a building, apparently a local pub, "+
        "just to the south, and another local business to "+
        "the west.";

    add_item(({"square","town square"}),"The town square is a "+
        "large, well-kept space at the center of "+
        "Gamwich.  Paths of dirt "+
        "head out from each of its four corners.\n");
    add_item(({"path","paths","road","roads","dirt path",
        "dirt paths","dirt road","dirt roads"}),
        "A dirt path heads out of each of the four corners of "+
        "the central square of Gamwich.  The closest path heads "+
        "southwest."+
        "\n");

    add_exit(GAMWICH_DIR+"sw_path_1","southwest");
    add_exit(GAMWICH_DIR+"square_se","east");
    add_exit(GAMWICH_DIR+"square_nw","north");
    add_exit(GAMWICH_DIR+"pub","south");
    add_exit(GAMWICH_DIR+"candleshop","west");

    make_the_room();

    reset_room();

}

