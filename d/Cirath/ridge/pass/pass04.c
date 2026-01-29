/* a_pass04.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are travelling along a path between two "+
              "huge mountains. The rocky landscape is as monotonous "+
              "as ever, and the heat is making your sight blurred. "+
              "Looking up toward the unyielding sun you almost wish "+
              "it was night, even though you know that then you would "+
              "freeze instead. You can struggle north along the path, "+
              "or head towards the civilized city of Tyr to the southeast,"+
              " where there is water to be bought.\n");
    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass05.c","north",0,1);
    add_exit(WILD_PASS+"pass03.c","southeast",0,1);
}
