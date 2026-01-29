/* a_pass02.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are travelling a trail leading into the mountains. "+
              "Here it seems to turn slightly, going along the "+
              "mountain range. The barren rocky landscape is devoid of "+
              "visible life, and the sun beats down relentlessly from "+
              "above. The trail continues to the west, and looking "+
              "southeast you can see the trail emerging onto a plain.\n");
    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass03.c","west",0,1);
    add_exit(WILD_PASS+"pass01.c","southeast",0,1);
}
