/* a_pass05.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are travelling along a path between two huge "+
              "mountains. The path is straight and it looks a bit easier "+
              "to travel northwards here. Some rocks seem to have been "+
              "thrown off the path, making it possible to travel at a faster "+
              "pace here, but conserving your strength for the travel ahead "+
              "might be wiser. Northwards the path goes down into a crevice, "+
              "and south the path continues.\n");
    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass06.c","north",0,1);
    add_exit(WILD_PASS+"pass04.c","south",0,1);
}
