/*
*   by Amelia for use in the Light Forest
*   updated, Maniac, 9/1/96
*/
inherit "/d/Calia/std/room_tell_room";
#include "pond.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

int frog;

void
reset_room()
{
	frog = 1;
}

void
create_room()
{
	
	set_short("In the pond");
	set_long("You are standing on a rock in the middle of the "+
		"pond, surrounded by water lilies and lily pads. There are "+
		"willow trees at the edge of the pond, which is "+
		"a short distance away. The rock is covered in pond slime "+
		"and is partially submerged. You can jump back "+
		"to the other rock from here, but there seems "+
		"to be no way to go forward.\n");

	add_item((({"rock", "rocks"})),
		"The rocks allow some foothold, but are very "+
		"slippery. You are standing on a rock which "+
		"is partially submerged. Some distance away is "+
		"another rock.\n");
	add_item((({"lily", "lilies", "water lilies", "water lily"})),
		("Pink and white water lilies nearly cover "+
		"the surface of the pond.\n"));
	add_item((({"tree", "trees", "willow trees", "willows", "willow"})),
		"Willow trees grow along the edge of the pond, "+
		"which is not far away now. You notice that one "+
		"tree is especially close. There is a branch which you "+
		"could reach, if you are really agile.\n");
	add_item((({"branch","bough","branches","boughs"})),
		"The branch hangs down like a rope or vine. "+
		"You could try to grab or reach it, and swing across "+
		"to shore.\n");
	add_item((({"pad", "pads", "lily pad", "lily pads"})),
		("The green leaves of the water lily are "+
		"a perfect place for frogs to hide.\n"));
	set_tell_time(90);
	add_tell("Croak, croak, croak!\n");
	add_tell("Chug-a-rumph, chug-a-rumph, chug-a-rumph!\n");
	add_tell("Bre-ke-ke-ke, koax! koax!\n");
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);

	reset_room();
	add_prop(OBJ_S_SEARCH_FUN, "find_frog");
	add_prop(OBJ_I_SEARCH_TIME, 5);

}

void
init()
{

	::init();
	add_action("go_back", "jump");
	add_action("go_back", "leap");
	add_action("go_back", "hop");
	add_action("reach_limb", "reach");
	add_action("reach_limb", "grab");
	add_action("reach_limb", "swing");

}


int
go_back(string str)
	{
		if((str=="back")||(str=="rock"))
			{
			write("You make like a frog and jump!\n");
			say(QCTNAME(TP)+" jumps back to the other rock.\n");
			TP->move_living("M", FPATH+"pond2", 1);
			say(QCTNAME(TP)+" jumps in.\n");
			write("You manage to just make it back to "+
				"the rock.\n");
			return 1;
			}
		notify_fail("Jump where?\n");
		return 0;
	}

string
find_frog(object searcher, string str)
	{
	object obj;
	object ob;
	string dummy;

	if (frog)
	{
	if((sscanf(str, "pad %s", dummy)==1)|| (str=="pad")||
	(sscanf(str, "lilies %s", dummy)==1) || (str== "lilies")||
	(sscanf(str, "lily %s", dummy)==1) ||(str=="lily")||
	(sscanf(str, "%s frogs", dummy)==1)||(str=="here for frogs")||
	(sscanf(str, "%s frog", dummy)==1)|| (str=="here for frog"))
		{
		obj = clone_object(FROG);
		frog = 0;
		obj->move(TO);
		TP->add_prop(PLAYER_I_FOUND_FROG, 1);
		return "Close by you spot a frog, sitting on "+
		"a lily pad.\n";
		}
	}

	ob = present("jeremiah");
	if(objectp(ob))
		return "You find a bullfrog.\n";
	return "You find nothing of interest.\n";
}

int
reach_limb(string str)
{


	if((str=="bough")||(str=="branch")||(str=="onto branch")||
		(str=="on bough")||(str=="on branch")||(str=="onto bough")||
		(str=="on to branch"))
	{
		write("You grab the branch and swing across to land.\n");
		say(QCTNAME(TP)+" grabs the willow branch and "+
		"swings across to shore.\n");
		TP->move_living("M",FPATH+"edge_pond.c",0,0);
		say (QCTNAME(TP)+" swings in and drops onto the ground.\n");
		write("You drop onto the ground.\n");
		return 1;
		}
	notify_fail("Grab what?\n");
	return 0;
}
