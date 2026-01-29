
/* sw_path_1.c
 * Town of Gamwich
 * Southwestern Path
 * Room 1 (Nearest the town square)
 * Created 27 February 1995 by Farlong
 */

inherit "/d/Shire/eastroad/eroad";

#include "defs.h"

object hobbit;

void
reset_room()
{
    if(!hobbit)
    {
        hobbit=clone_object(ER_DIR+"npc/mhobbit");
        hobbit->arm_me();
        hobbit->move(TO);
    }
}

void
create_room()
{
    area="in";
    areaname="Gamwich";
    land="the West Farthing of the Shire";
    areatype=11;
    areadesc="path";
    grass="wild";

    extraline="Two stout buildings stand nearby: a candleshop to the "+
        "north; and the local pub, the Golden Wheelbarrow, "+
        "to the east.  This well-kept dirt path enters the town square "+
        "to the northeast, and continues toward one of "+
        "the local hobbit-holes in the opposite direction.";

    add_item(({"square","town square"}),"The town square is a "+
        "large, well-kept space at the center of "+
        "Gamwich.  It lies just to the northeast.\n");
    add_item(({"path","paths","road","roads","dirt path",
        "dirt paths","dirt road","dirt roads"}),
        "A dirt path heads out of each of the four corners of "+
        "This dirt path is quite well-tended by the local "+
        "hobbits.  It heads from northeast to southwest.\n");

    add_exit(GAMWICH_DIR+"sw_path_2","southwest");
    add_exit(GAMWICH_DIR+"square_sw","northeast");
    add_exit(GAMWICH_DIR+"candleshop","north");
    add_exit(GAMWICH_DIR+"pub","east");

    make_the_room();

    reset_room();

}

