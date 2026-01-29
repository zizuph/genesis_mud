// Underwater cave   (/d/Avenir/common/port/uw6.c)
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


public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in a cave");
    set_long("You are inside a seemingly fathomless underwater cave. " +
      "It is difficult to see anything in the pervasive darkness, making it " +
      "impossible for you to estimate the size of the cave. "+
      "The irregularity you saw before has solidified into an old shipwreck. "+
      "The deck of the ship is to your northwest, and the cabinhouse " +
      "to your west. South of you, the opening you entered through is " +
      "barely visible as a lighter shade of grey in the shadows.\n");
    add_item(({"wreck","shipwreck","irregularity"}),
      "Amazing. This ship must have been swallowed by the currents and somehow " +
      "transported into this cave. You can tell it has been here for a long " +
      "time since the seaweed is growing richly along the hull.\n");
    add_item(({"cabinhouse","cabin"}),
      "The cabinhouse is too far away to really make out anything of it. You " +
      "see it only as an outline to your west.\n");
    add_item(({"deck","mast"}),
      "The deck is up to your immediate northwest. The mast is broken alittle " +
      "less than halfway up, and falls back towards the deck like a symbol of " +
      "lost glory.\n");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"cliff","rock","wall","floor","ceiling","walls"}),
      "You cannot really see it, there is only blackness.\n");
    add_item(({"opening"}),
      "The exit from the cave is visible to your southwest as a lighter shade " +
      "in the darkness.\n");

    add_exit(PORT + "uw9", "north");
    add_exit(PORT + "uw9", "northeast");
    add_exit(PORT + "uw8", "east");
    add_exit(PORT + "uw4", "southeast");
    add_exit(PORT + "uw4", "south");
    add_exit(PORT + "uw4", "southwest");
    add_exit(PORT + "uw5", "west");
    add_exit(PORT + "uw8", "northwest");
}
