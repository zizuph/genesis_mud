/* a_pass17.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are standing on a path leading up a mountain. "+
              "The path turns westward around a huge rock here, while "+
              "still climbing upwards. It also continues downwards "+
              "towards the southeast. Your legs are aching while "+
	      "walking this path, as the combination of a rocky path, "+
              "thin air and a blazing sun upon your head makes your "+
              "journey a suffering worthy of the most dedicated "+
              "self-tormentor.\n");

    ROCK;
    SUN;
    TRAIL;
    OUTSIDE
    add_exit(PASS_DIR+"a_pass18.c","west","@@westwards",3);
    add_exit(PASS_DIR+"a_pass16.c","southeast",0,3);
}

int westwards()
{
	write("Going past the rock, a sudden dizziness hits "+
              "you. You almost topple over the edge, but manage "+
              "to stumble to safety.\n");
        return 0;
}
