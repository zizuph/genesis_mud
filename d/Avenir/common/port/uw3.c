// Underwater room   (/d/Avenir/common/port/uw3.c)
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
    if ((str == "west") || (str == "south"))
    {
	return "You decide that isn't a good idea, since the currents "+
	    "seem dangerous in that direction.\n";
    }
    else if (str == "down")
    {
	TP->add_fatigue(-(calc_fat(TP) / 2));
	return "You dive further down, but the pressure is so " +
	    "strong you instantly return.\n";
    }

    return "";
}

public int
swim_exit(void)
{
    if (swim_dir == "north")
	write("You swim into the darkness.\n");

    return 0;
}

public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in the dark lake");
    set_long("You are swimming in murky dark water. Powerful " +
      "currents are dragging you in various directions. The dim light from " +
      "the surface is weaker here. Below you is only darkness. To your north " +
      "the cliff appears like darkness within darkness, so dark you can not " +
      "even be sure it is there.\n");
    add_item(({"water","currents"}),
      "The dark water envelops you completely. Luckily the currents here " +
      "are moving you towards the cliff, rather than away from it. You " +
      "don't know what could happend if you got caught in the currents.\n");
    add_item(({"cliff","rock"}),
      "You cannot really see it, there is only blackness.\n");
    add_item(({"surface"}),
      "A faint glow above your head indicates that the surface is far " +
      "above you. It looks like your best option.");

    add_exit(PORT + "uw2", "up");
    add_exit(PORT + "uw4", "north");
    add_exit(PORT + "uw3a", "east");
}
