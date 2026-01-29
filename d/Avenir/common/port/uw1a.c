// Underwater room   (/d/Avenir/common/port/uw1a.c)
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
    if ((str == "east") || (str == "south"))
    {
	return "You decide that isn't a good idea, since the currents "+
	    "seem dangerous in that direction.\n";
    }
    else if (str == "north")
    {
	return "The cliff blocks your way.\n";
    }

    return "";
}

public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in the dark lake");
    set_long("You are swimming in dark, murky water. Powerful " +
      "currents are pulling you in various directions. Above you, the " +
      "surface of the lake is a faint glowing light. Below you is only " +
      "darkness. You cannot make out the details of the cliff surface to "+
      "the north but it is there, the only steady point in your environment.\n");
    add_item(({"water","currents"}),
      "The dark water envelops you completely. Luckily the currents here " +
      "are moving you towards the cliff, rather than away from it. You " +
      "don't know what could happend if you got caught in the currents.\n");
    add_item(({"cliff","rock"}),
      "The dark rock of the cliff appears only as a darker shade in the " +
      "darkness surrounding you.\n");
    add_item(({"surface"}),
      "A faint glow above your head indicates that the surface is right " +
      "above you. It looks like your best option.");

    add_exit(PORT + "water2", "up");
    add_exit(PORT + "uw2a", "down");
    add_exit(PORT + "uw1", "west");
}
