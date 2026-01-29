/* a_pass16.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are standing on a path. "+
              "The path continues northwest here, where it goes up "+
              "a mountain, or southeast towards a crevice in the "+
              "ground. With the sun beating down on you, and the "+
	      "air getting thinner the further up you go, you really "+
              "don't relish the thought of going upwards.\n");

    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass17.c","northwest",0,2);
    add_exit(WILD_PASS+"pass15.c","southeast",0,2);
}
