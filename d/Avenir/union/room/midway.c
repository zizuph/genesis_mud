/* A place midway between the overhang steps and the ledge
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>


public void
union_room(void)
{
    set_short("side of the abyss");
    set_long("You are hanging by your fingers and your toes to the "+
	"side of the abyss. The stone is very warm, almost hot. You "+
	"can feel the heat pressing upon you like a giant hand. "+
	"Several meters below is a small ledge that runs just a "+
	"handspan above the river of molten rock. Above you can see "+
	"hand-holds leading up to the relative safety of the square "+
	"landing.\n");

    add_item(({"ledge"}), "It is a bit of a ways down. You think you "+
	"can reach it if you are careful.\n");
    add_item("overhang", "There lies safety, if you have the courage "+
	"and strength to climb up to it.\n");
    add_item(({"lake","molten rock","lava","down","river","rock"}),
	"The river of lava is down below. Its heat is ovewrwhelming, "+
	"even at this height.\n");
    add_item(({"wall","walls","chasm", "chasm wall", "abyss"}),
	"The walls of the chasm rise sheer and smooth, with only "+
	"a few hand-holds marring the surface.");
    add_item(({"hand-hold", "handhold", "handholds", "hand-holds"}),
	"If you are careful, you should be able to use the handholds "+
	"to climb back up the chasm wall.\n");

    add_exit("overhang_steps", "up", 0, 10, 1);
    add_exit("ledge", "down", 0, 10, 1);
}

public int
do_climb(string str)
{
    if (str == "up")
    {
	write("You climb up to the edge and swing yourself up over "+
	    "the side of the overhang.\n");
	say(QCTNAME(TP)+" pulls "+ HIM(TP) +"self upward, climbing "+
	    "to safety.\n");

	TP->add_fatigue(10);
	TP->move_living("M", ROOM + "overhang_steps", 1, 0);
	return 1;
    }
    else if (str == "down")
    {
	write("You continue to inch yourself down the wall of "+
	    "the abyss.\n");
	say(QCTNAME(TP) +" bravely continues down the side of "+
	    "the cliff.\n");

	TP->add_fatigue(10);
	TP->move_living("M", ROOM +"ledge", 1, 0);
	return 1;
    }

    NF("Climb where? Up or down?\n");
    return 0;
}

public void
init(void)
{
    ::init();
    add_action(do_climb, "climb");
}
