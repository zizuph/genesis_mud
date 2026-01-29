/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A medium-income hobbit hole
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>


inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

//Is there a toy to find by searching?
int is_toy = 1;

//Any parent will realize how agonizing it is to step on children's toys.
int
block_people()
{
	write("\nOn your way out of the bedroom, you step on one of the "
		+ "toys.\nOUCH!\n\n");
	return 0;
}

void reset_shire_room();

void
create_hobbit_room()
{
	set_short("In the Children's Bedroom");
	
	set_long("Inside the children's bedroom, you notice a bunk bed against "
		+ "the wall. Next to the bunk bed is a dresser. There are toys strewn "
		+ "about the floor, as if they have been recently played with, while "
		+ "the light from the window bathes the room in a soft, happy glow. "
		+ "\n");
	
	add_prop(OBJ_S_SEARCH_FUN, "search_floor");
	
	add_walls();
	add_bedroom_child("bunk bed");
	add_window("colorful");
	
	add_exit(WAYM_HOUSE_DIR + "h_3_5", "south", block_people);	//Hallway

}

void
reset_shire_room()
{
	is_toy = 1;
}

void
init()
{
	::init();

	
}

public string
search_floor(object me, string arg)
{
	if(arg == "toys" | arg == "toy")
	{
	if(is_toy == 1)
	{
		object ball;
		ball = clone_object(WAYM_OBJ_DIR + "ball1");
		say(QCTNAME(TP) + " finds a " + ball->query_short() + " in the "
			+ "pile of toys!\n");
		is_toy = 0;
		ball->move(TP);
		return("You find a " + ball->query_short() + " in the toys!\n");
	}
	else
	{
		return "";
	}
	}
	else
		return "";
}