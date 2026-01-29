// Underwater room   (/d/Avenir/common/port/uw2a.c)
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

private int searched;

public void
reset_room(void)
{
    searched = 0;
}

public string
do_search(object searcher, string str)
{
    object ob;

    if (searched || (str != "crack"))
	return "";

    ob = clone_object(PORT + "obj/uw_driftwood");
    ob->move(searcher);
    searched = 1;

    return "Your hands find an item in the dark crack.\n";
}

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
      "currents are pulling you in various directions. Far above you, the " +
      "surface of the lake is a faint glowing light. Below you is only " +
      "darkness. You can make out a small crack in the cliff surface to "+
      "the north of you.\n");
    add_item(({"water","currents"}),
      "The dark water envelops you completely. Luckily the currents here " +
      "are moving you towards the cliff, rather than away from it. You " +
      "don't know what could happend if you got caught in the currents.\n");
    add_item(({"crack","cliff","rock"}),
      "You can barely make out a small crack in the surface of the cliff " +
      "which looms to your north.\n");
    add_item(({"surface"}),
      "A faint glow above your head indicates that the surface is somewhere " +
      "above you. It looks like your best option.");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 4);

    add_exit(PORT + "uw1a", "up");
    add_exit(PORT + "uw3a", "down");
    add_exit(PORT + "uw2",  "west");
}
