/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("Some sticks, perhaps from a tree used for firewood, " +
        "rest in a small pile. The thickness of the forest prevents " +
        "movement in many directions, except to the northeast and " +
        "northwest, as well as south.\n");
    AI(({"sticks","pile of sticks","small pile","pile"}),"It is pile " +
        "of discarded wood and sticks.\n");
    AI("stick","There are many sticks.\n");
    AI(({"discarded wood","wood"}),"The discarded wood are sticks and " +
        "branches, not worth taking for firewood.\n");
    add_search(({"pile of sticks","small pile","pile"}),3,
        TWEP + "stick_club",-2);


    AE(TROOM + "road7", "northwest", 0, 2, 1);
    AE(TROOM + "forest7", "northeast", 0, 2, 1);
    AE(TROOM + "forest5", "south", 0, 2, 1);

    reset_tant_room();
}

