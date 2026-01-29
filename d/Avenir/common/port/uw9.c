// Underwater cave   (/d/Avenir/common/port/uw9.c)
// creator(s):       Glinda may -95
// last update:
// 		Lucius, Jan 2009: Re-written for new water code.
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"


public string
hook_no_swim(string str)
{
    if ((str == "north") || (str == "northeast") || (str == "northwest"))
    {
	return "You swim into the cave wall.\n"+
	    "You had no idea it was so close.\n";
    }
}

public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in a cave");
    set_long("You are inside what seems to be an immense underwater " +
      "cave. You find it difficult to see anything in the vast darkness. "+
      "You are now close to the fore hull of the old shipwreck. Seaweed "+
      "grows thickly here, the green tendrils wavingly slowly as you "+
      "pass. You should be able to reach the deck of the ship by swimming "+
      "up to the southwest. Far off to the south the opening you entered "+
      "through is barely discernable as a lighter shade of grey in the "+
      "dimness.\n");
    add_item(({"wreck","shipwreck","irregularity","hull"}),
      "Amazing. This ship must have been swallowed by the currents and "+
      "somehow transported into this cave. You can tell it has been here "+
      "for a long time since the seaweed is growing richly along the hull.\n");
    add_item(({"deck","mast"}),
      "The deck is up to your immediate southwest. The mast is broken "+
      "a little less than halfway up, and falls back towards the deck "+
      "like a symbol of lost glory.\n");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"cliff","rock","wall","floor","ceiling","walls"}),
      "You cannot really see it, there is only blackness.\n");
    add_item(({"opening"}),
      "The exit from the cave is visible to your southwest as a lighter "+
      "shadow in the darkness.\n");
    add_item(({"hull", "fore hull"}),
      "It appears to be relatively intact. It must have been well-"+
      "constructed to have withstood this many years beneath the water.\n");
    add_item(({"seaweed", "tendrils"}),
      "It is a lush aquatic garden of green lace which grows around "+
      "the ship's hull.\n");

    add_exit(PORT + "uw7", "east");
    add_exit(PORT + "uw6", "southeast");
    add_exit(PORT + "uw6", "south");
    add_exit(PORT + "uw8", "southwest");
    add_exit(PORT + "uw8", "west");
}

