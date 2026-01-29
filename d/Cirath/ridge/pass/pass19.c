/* a_pass19.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are standing on a path leading sharply up a mountain. "+
              "Looking up towards the south you see a ledge, but "+
              "nothing past it. Could the end of this infernal "+
              "mountain path be there, or is the heat playing tricks "+
              "on you? Perhaps you should go and take a look, or perhaps "+
              "it is safer to head down the path to the northeast, as the "+
              "strength it takes to climb up there very well might mean the "+
              "difference between life and death in this harsh environment.\n");


    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass20.c","south","@@southwards",2);
    add_exit(WILD_PASS+"pass18.c","northeast",0,2);
}

int southwards()
{
	write("With a grunt of effort you climb up the slope "+
              "to find yourself standing at the top.\n");
	return 0;
}
