
 /* Digit 03 JUNE 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"


void
create_room()
{
    set_short("In a watery passage");
    set_long("You are standing in a passage in which water is running "+
        "down the walls like a waterfall, and disappears into the floor "+
        "like magic.  To the north you see a large chamber with what "+
        "appears to be a fountain in the centre of it.  The passage "+
        "continues to the south as well.\n");

    add_item(({"water","walls"}),"The water seems to appear out of "+
        "nowhere where the ceiling meets the beginning of the walls, "+
        "and disappears mysteriously where the walls meet the floor.  "+
        "It is warm to the touch, and gives the air a refreshing smell.\n");

    add_exit(CAVE+"water/room2","north");
    add_exit(CAVE+"water/entrance","south");
}

