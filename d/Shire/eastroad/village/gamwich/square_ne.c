
/* square_ne.c
 * Town of Gamwich
 * Town Square
 * NE corner
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
        hobbit=clone_object(ER_DIR+"npc/wehobbit");
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
    grass="an interesting hybrid";  /*smirk*/

    extraline="The town square is small and well-kept.  Its "+
        "edges extend to the west and south here, and a small "+
        "dirt path heads northeast amongst the hobbit-homes.";

    add_item(({"square","town square"}),"The town square is a "+
        "well-kept space at the center of "+
        "Gamwich.  Paths of dirt "+
        "head out from each of its four corners.\n");
    add_item(({"path","paths","road","roads","dirt path",
        "dirt paths","dirt road","dirt roads"}),
        "A dirt path heads out of each of the four corners of "+
        "the central square of Gamwich.  The closest path heads "+
        "northeast, amongst the hobbit-homes, called "+
        "smials.\n");

    add_exit(GAMWICH_DIR+"ne_path_1","northeast");
    add_exit(GAMWICH_DIR+"square_se","south");
    add_exit(GAMWICH_DIR+"square_nw","west");

    make_the_room();

    reset_room();

}

