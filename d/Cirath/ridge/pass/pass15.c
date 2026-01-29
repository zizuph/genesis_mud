/* a_pass15.c: Pass into mountains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are standing by a crevice. "+
              "The path continues northwest here, where it goes up "+
              "a mountain, or south into the crevice by your feet. "+
              "Thinking of the strenous task of climbing the mountain "+
              "in this heat, you find the coolness the crevice seems "+
              "to offer much more compelling.\n");

    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass16.c","northwest",0,2);
    add_exit(WILD_PASS+"pass14.c","south",0,2);
}
