/*
*   by Amelia for use in the Light Forest
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "pond.h"


create_room() {

	set_short("At the far edge of the pond");
	set_long("You are in a small clearing at the far side of "+
		"the pond. The clearing is circled by tall trees. "+
		"The forest joins with the willows that edge the pond, "+
		"providing a comfortable shade. Under your feet you feel "+
		"a cushion of springy moss. To one side beneath the eaves "+
		"of an old willow tree, you spot a dilapidated hut. "+
		"Although it's shady here, the forest seems filled with "+
		"diffused light.\n");
	add_item((({"tree", "trees", "oak trees", "maple trees"})),
		("The trees here are part of the Calian forest. "+
		"You see oaks, maples, birch and graceful pine trees. "+
		"Along the edge of the pond, are a row of willow trees "+
		"with boughs that bend over the water. There is a bough "+
		"near to you, that you could grab and return to "+
		"the rock in the middle of the pond.\n"));
	add_item((({"bough", "boughs", "branch", "branches"})),
		"The willow branches are slim and flexible as ropes "+
	"or vines. You see one close by, that you could grab "+
		"and swing out to the rock in the pond.\n");
	add_item((({"forest"})),
          ("The forest seems filled with diffused sunlight.\n"));
	add_item((({"grass", "moss"})),
		("Soft moss feels like a cushion beneath your feet.\n"));
	add_item((({"hut", "dilapidated hut"})),
		("The old hut looks like it might have once been "+
		"a boathouse or was perhaps used for storage. There "+
		"is an old wooden boat, with holes in its bottom, propped "+
		"against one side. You see an old door, falling off "+
		"its hinges, and open. You might be able to enter "+
		"there.\n"));
	add_item((({"bird", "birds","animal","animals","small animals"})),
		("Every now and then you catch a glimpse of "+
		"a sparrow, chipmunk, or squirrel.\n"));


	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);
}


void
init()
{

	::init();
	add_action("enter_hut", "enter");
	add_action("reach_branch", "grab");
	add_action("reach_branch","reach");
	add_action("reach_branch", "swing");
}

int
enter_hut(string str)
{

	if ((str=="hut")||(str==""))
	{
		write("You enter the hut.\n");
		say(QCTNAME(TP)+" enters the hut.\n");
		TP->move_living("M",FPATH+"hut.c",0,0);
            tell_room(environment(TP), QCTNAME(TP)+" arrives.\n",
		({TP}));
	return 1;
}
notify_fail("Enter what?\n");
	return 0;
}


int
reach_branch(string str)
{

	if((str=="branch")||(str=="bough")||(str=="onto branch")||
	(str=="on branch")||(str=="on bough")||(str=="onto bough"))
		{
		write("You grab onto the branch and swing "+
		"through the air.\n");
		say(QCTNAME(TP)+ " grabs a willow branch and swings "+
		"out through the air.\n");
		TP->move_living("M",FPATH+"pond3.c",0,0);
		write("You land on the rock.\n");
		say(QCTNAME(TP)+" lands on the rock.\n");
		return 1;
	}
	notify_fail("Grab what?\n");
	return 0;
}
