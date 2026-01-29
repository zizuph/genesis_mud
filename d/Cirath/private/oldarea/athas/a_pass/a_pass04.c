/* a_pass04.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are are travelling along a path between two "+
              "huge mountains. The rocky landscape is as monotonous "+
              "as ever, and the heat is making your sight blurred. "+
              "Looking up toward the unyielding sun you almost wish "+
              "it was night, even though you know that then you would "+
              "freeze instead. You can struggle north along the path, "+
              "or head towards the civilized city of Tyr to the southeast "+
              ", where there is water to be bought.\n");
    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(PASS_DIR+"a_pass05.c","north",0,1);
    add_exit(PASS_DIR+"a_pass03.c","southeast",0,1);
}
