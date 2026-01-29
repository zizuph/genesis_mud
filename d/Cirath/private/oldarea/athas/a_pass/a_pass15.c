/* a_pass15.c: Pass into mountains. */

inherit "/std/room";
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
    add_exit(PASS_DIR+"a_pass16.c","northwest",0,3);
    add_exit(PASS_DIR+"a_pass14.c","south",0,5);
}
