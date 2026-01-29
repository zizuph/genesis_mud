// water1           (/d/Avenir/common/port/water1.c)
// creator(s):       Glinda may -95
// last update:
// 		Lucius, Jan 2009: Re-written for new water code.
// purpose:          From here you dive into the underwater.
//
// note:
// bug(s):
// to-do:void

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

public int
do_climb(string str)
{
    if (str != "ledge")
	return NF("Climb where?\n");

    int fat = calc_fat(TP);

    if (TP->query_fatigue() < fat)
    {
	write("You are too tired to move in that direction.\n");
    }
    else if (TP->query_skill(SS_CLIMB) < random(20))
    {
	write("You try to climb the ledge, but slide back into the water.\n");
	TP->add_fatigue(-(fat / 2));
    }
    else if (!TP->move_living("climbing up on the ledge", PORT + "ledge", 1))
	TP->add_fatigue(-fat);

    return 1;
}

public string
hook_no_swim(string str)
{
    if ((str == "west") || (str == "south"))
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

public int
swim_exit(void)
{
    if (swim_dir != "down")
	return 0;

    int swim_skill = TP->query_skill(SS_SWIM);
    if (swim_skill < 30)
    {
	if (swim_skill > 0)
	    write("Maybe you should learn to swim alittle better first?\n");
	else
	    write("You cannot swim! Much less dive.\n");

	return 1;
    }

    write("You dive into the cold dark water.\n");
    return 0;
}

public void
create_room(void)
{
    water_room();

    set_short("In water");
    set_long("You are swimming in dark, murky water. Powerful " +
      "currents are pulling you in various directions. Right to the north " +
      "is a small ledge you might be able to climb onto. The cliff you " +
      "dived from is further east.\n");
    add_item(({"water","currents"}),
      "The dark water is all around you. Luckily the currents here " +
      "are moving you towards the cliff, rather than away from it. You " +
      "don't know what could happend if you got caught in the currents.\n");
    add_item(({"cliff","rock"}),
      "The cliff is to the east. Going back there is probably not a bad idea.\n");
    add_item(({"ledge"}),
      "There is a small ledge immediately to your north. You might be able to " +
      "climb it.\n");

    add_exit(PORT + "water2", "east");
    add_exit(PORT + "uw1", "down");
}

public void
init(void)
{
    ::init();
    add_action(do_climb, "climb");
}

