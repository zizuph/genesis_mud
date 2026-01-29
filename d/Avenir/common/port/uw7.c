// Underwater cave   (/d/Avenir/common/port/uw7.c)
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
    if ((str == "east") || (str == "northeast") || (str == "southeast"))
    {
	return "You are stopped by the cavewall.\n"+
	    "You had no idea it was so close.\n";
    }
    return "";
}

public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in a cave");
    set_long("You are inside a seemingly fathomless underwater cave. " +
      "It is difficult to see anything in the pervasive gloom, making it " +
      "impossible for you to estimate the size of the cave. "+
      "To the southwest the opening you entered through is barely visible "+
      "as a lighter shadow in the darkness.\n");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"cliff","rock","wall","floor","ceiling","walls"}),
      "You cannot really see it, there is only a solid blackness which assures "+
      "you that it is there.\n");
    add_item(({"opening"}),
      "The exit from the cave is visible to your southwest as a lighter shadow " +
      "in the darkness.\n");

    add_exit(PORT + "uw9", "north");
    add_exit(PORT + "uw4", "south");
    add_exit(PORT + "uw4", "southwest");
    add_exit(PORT + "uw6", "west");
    add_exit(PORT + "uw9", "northwest");
}
