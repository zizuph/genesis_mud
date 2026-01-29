/*
*   by Amelia for use in the Light Forest
*/
inherit "/std/room";
inherit "/d/Calia/mountain/special/room_tell";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "defs.h"


void
create_room()
{
	
	set_short("In the middle of the pond");
	set_long("You are standing on a rock in the middle of the "+
		"pond. All around you are water lilies. You see a grey "+
		"shape off to your right, partially submerged, which "+
		"appears to be another rock. On the far side of the pond, "+
		"willow trees bend graceful boughs over the water. "+
		"The shore and forest path seem far away. You might "+
		"be able to make it if you jump though.\n");
		
	add_item((({"rock", "rocks", "slippery rock"})),
		("You are standing on a rock covered in pond slime, "+
		"so it's fairly slippery here.  A short distance away you "+
		"see a shape that looks like another rock.\n"));
	add_item((({"water lily", "lily", "lilies", "water lilies"})),
		("The water lilies are large pink flowers surrounded "+
		"by great green lily pads.\n"));
	add_item((({"frog", "frogs"})),
		"Every now and then you see a flash "+
		"of green out of the corner of your eye, "+
		"followed by a splash.\n");
	add_item((({"shore", "back"})),
		("The shoreline seems very far away.  "+
		"If you are very agile, you might just make it "+
		"if you jump back to the shore.\n"));
	add_item((({"pad", "pads", "lily pad", "lily pads"})),
		("Partially submerged among the pads you can "+
		"just make out a large grey shape off to your right.\n"));
	add_item((({"shape", "grey shape", "large grey shape"})),
		("The large grey shape off to your right looks "+
		"like it might be another rock.  You could try "+
		"to jump there, if you are agile enough.\n"));
	add_item((({"trees", "willow trees", "willows", "branches"})),
		("The willow trees grow right on the edge of "+
		"the pond, and their graceful trailing branches "+
		"extend over the water on the far side.\n"));
	
	set_tell_time(90);
	add_tell("You see a flash of green and hear, Splash!\n");
	add_tell("Croak, croak, croak, croak!\n");
	add_tell("Neek-a-neek-a-neek-a-neek!\n");
	add_tell("Chugarumph, chugarumph, chugarumph!\n");
	add_tell("Ribbit, ribbit, ribbit, ribbit!\n");

	add_prop(OBJ_S_SEARCH_FUN, "search_stuff");
	add_prop(OBJ_I_SEARCH_TIME, 5);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);
}


void
init()
{
	::init();
	add_action("find_next", "jump");
	add_action("find_next", "leap");
	add_action("find_next", "hop");
}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob,from);
	start_room_tells();
}


int
find_next(string str)
{
	if((str=="rock")||(str=="on rock")||(str=="to rock")||
		(str == "shape")||(str=="to shape"))
	{
		write("You make like a frog and jump!\n");
		TP->move_living("M",FPATH+"pond3",1);
		say(QCTNAME(TP)+" leaps to the rock.\n");
		write("You just made it to the rock.\n");
		return 1;
	}
	if ((str=="back")||(str=="shore")||(str=="to shore"))
		{
		write("You make like a frog and jump!\n");
		TP->move_living("M",FPATH+"pond1", 1);
		write("You jump back to shore.\n");
		say(QCTNAME(TP)+" jumps in.\n");
		return 1;
		}
	notify_fail("Jump where?\n");
	return 0;
}

string
search_stuff(object searcher, string str)
	{
		if((str=="here for frog")||(str=="here for frogs"))
		{
		return "You find nothing. The frogs are too well "+
		"camouflaged.\n";
		}
	return "You find nothing of interest.\n";
}
