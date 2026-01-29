/*
 * 1k3.c
 * Castle Telberin's Armoury
 * Unknown original author
 * Re-described and updated by Alaron August 16,1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Armoury");
    set_long("   You stand in the armoury of Castle Telberin. The room "+
	     "is undecorated and has a cold, unforgiving feel to it. The "+
	     "north wall has a bench sitting up against it. Pegs beneath "+
	     "the tapestry on "+
	     "the north wall provide support for hung quivers, bows "+
	     "and other weapons. The east wall is filled with several "+
	     "storage closets, probably containing more weapons and "+
	     "armour. The west wall is dominated by a heavy rack of "+
	     "weapons.\n\n");

    add_item("bench", "The bench is made of solid oak. There are a few pairs " +
             "of boots under the bench.\n");
    add_item("pegs", "The pegs are neatly spaced apart.  There are some Elven " +
             "cloaks hanging on the pegs.\n");
    add_item(({"cloaks", "elven cloaks"}),
	     "They look to be fine, elven-made cloaks.\n");
    add_item("tapestry", "The tapesty hangs on the north wall. The tapesty " +
             "is a collage of different fighting scenes. One scene is showing " +
             "Elven men riding upon white horses heading into battle.  Another " +
             "scene shows an Elven Knight pulling his sword from a dragon. " +
             "All the scenes are of Elven men in combat.\n");
    add_item(({"closet","closets"}), "The closets appear to be made of the " +
             "same dark oak that the bench is made of. They all appear to " +
             "be locked.\n");
    add_item("rack", "The rack is made of solid dark oak.  The rack holds " +
             "several weapons including swords, polearms, clubs, bows " +
             "and few quivers of arrows.\n");               
   
    add_exit(CASTLE_DIR + "1k2","south",0);


}

