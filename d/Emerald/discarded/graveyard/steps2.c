/*
 * STEPS.c
 * Steps outside the church near the graveyard.
 *
 * Rework by Alaron July 26, 1996
 */

inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("Church south of the ocean inlet");
    set_long("   You stand amidst a pool of slowly swirling mist and "+
	     "fog. The dark, gray atmosphere thins enough to reveal the "+
	     "outside of an old, decaying church to the south. Putrid, "+
	     "rancid smells drift through the fog from the church to "+
        "assault your senses. Far " +
	     "dark gray shadows of broken and leaning gravestones. Far "+
	     "an ocean inlet at the end of the road.\n\n");
 
    add_item(({"church", "old church", "decaying church",
	       "old decaying church"}),
	     "It is an ancient, small church. It is a simple stone square "+
	     "design made of gray stone and painted white with a powdered "+
	     "stone and water mixture which is now cracking and flaking. "+
	     "It seems like a miracle that the roof is even on top of the "+
	     "church; the beams and support structure having skewed off "+
	     "of the east side of the base long ago. You can't quite "+
	     "determine the reason, but you feel a sense of dread and "+
	     "impending disaster oozing from the fog surrounding this "+
	     "church.\n");

    add_item( ({"mist", "fog", "atmosphere", "dark atmosphere"}),
	     "The dark gray mist swirls slowly about the entire area, "+
	     "almost creating a feeling of nausea as it almost makes "+
	     "you feel like the ground is spinning around you at your "+
	     "feet. The mist swirls slowly about you, yet you suddenly "+
	     "realize that you feel no breeze! You wonder what is "+
	     "propelling the dark mist.\n");
    
    add_item( ({"inlet", "ocean inlet", "end of road", "road"}),
	     "The ocean inlet at the end of the road is too distorted by the "+
	     "fog to make out any details.\n");
 
    add_exit(KROAD_DIR + "eroad13", "north", 0);
    add_exit(GRAVEYARD_DIR + "church", "south", 0);
}

int
new_block()
{
    write("There seems to be a wizard-wall here. Perhaps it will "+
	  "be removed soon?\n");
    return 1;
}

