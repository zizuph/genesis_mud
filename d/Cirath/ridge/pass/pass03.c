/* a_pass03.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are are travelling along a path between two "+
              "huge mountains. The rocky landscape makes it "+
              "difficult to move swiftly, and rocks balance precariously "+
              "on the cliff edges above. The sun is ever relentless, "+
              "but in here between the peaks it does not reach all "+
              "the way down. However relieved this makes you, the "+
              "travelling is hard work, and you cannot avoid building "+
              "up a good sweat.\n");
    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass04.c","northwest",0,1);
    add_exit(WILD_PASS+"pass02.c","east",0,1);
}
