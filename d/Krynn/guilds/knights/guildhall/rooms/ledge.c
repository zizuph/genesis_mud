/* by Morrigan Dec 7 1996, modified from Aridor's old outer VK walls */
#include <ss_types.h>
#include <macros.h>
#include "../../local.h"

inherit OUT_BASE;

create_vin_room()
{
    set_short("A small ledge");
    set_long("@@long_desc");
    AI(({"keep", "castle", "stronghold"}), "@@keep");
    AI("wall","The wall stands tall. It seems that people have tried to " +
      "climb it in the past, but have all failed.\n");
    AI(({"small piece of land","piece of land","land"}),"This small piece " +
      "lands juts out into the Vingaard River.\n");
    AI(({"vingaard river","river"}),"The Vingaard River flows northwards " +
      "to Kalaman.\n");
    AI("riverbank","The riverbank has a small tunnel that can be entered.\n");
    AI("tunnel","The tunnel undoubtedly leads under Vingaard Keep.\n");
    AI("walls","The walls of Vingaard Keep loom above you.\n");
    AI("ledge","The ledge that you are standing on is a small " +
      "piece of land. Perhaps it was an oversight by the " +
      "builders of Vingaard Keep.\n");
}

init()
{
    add_action("do_enter", "enter");
    add_action("climb_up", "climb");
    ::init();
}

int
do_enter(string str)
{
    NF("Enter what?\n");
    if (!str)
	return 0;

    if (str != "tunnel")
	return 0;

    set_dircmd("tunnel");
    write("You enter the tunnel.\n");
    TP->move_living("into the tunnel", "/d/Krynn/solamn/splains/room/secret5");
    return 1;
}

string
long_desc()
{
    return "You are on a small piece of land at the bottom of the western "+
    "wall of Vingaard Keep. Undoubtedly, you found your way here " +
    "through the tunnel that passes under the river. The tunnel " +
    "emerges from the riverbank a few inches above the surface of " +
    "the water, so you could enter it again to leave, because you don't see "+
    "any other exit, unless you can fly up a forty foot wall.\n";
}

int
climb_up(string str)
{
    int climbsk = TP->query_skill(SS_CLIMB);
    int success = climbsk - 69 - random(5);
    object *team;
    int i;

    NF("Climb what?\n");
    if (str != "wall")
	return 0;

    if (TP->query_race_name() == "draconian")
    {
	team = TP->query_team();

	TP->move(VROOM + "nwtowerup");
	tell_room(E(TP), "The draconian team manages to scale the walls "+
	  "with their claws.\n");
	for (i = 0; i < sizeof(team); i++)
	{
	    team[i]->move(VROOM + "nwtowerup");
	}
	return 1;
    }

    if (success > 0)
    {
	write("The experienced climber that you are, you easily pick " +
	  "your handholds and footholds. Still, this is one of the toughest " +
	  "climbs you've ever had. Finally you manage to pull yourself "+
	  "up onto the wall.\n");
	TP->move_living("climbing up the wall", VROOM + "nwtowerup");
	return 1;
    }
    if (success > -20)
    {
	TP->heal_hp(-300);
	write("You manage to get high up on the wall, but suddenly you " +
	  "just can't find another handhold. Clinging to the wall, you " +
	  "have to let go and fall all the way down on the path. OUCH!\n");
	if (TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }
    if (success > -40)
    {
	TP->heal_hp(-100);
	write("You manage to pick a few handholds, but you are rather " +
	  "clueless how to make it up all the way. You decide to give up " +
	  "and drop back down onto the path.\n");
	if (TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You try to climb up, but you have no clue how to hold onto " +
      "the wall so you give up.\n");
    return 1;
}

