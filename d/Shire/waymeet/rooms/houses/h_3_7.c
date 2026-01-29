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

int hat_pin = 1;

void reset_shire_room();

void
create_hobbit_room()
{
	set_short("In the Master Bedroom");
	
	set_long("A large, spacious room, the Master bedroom looks quite "
		+ "comfortable. You see a large bed against the wall, one of "
		+ "the largest you've seen in any smial. The floor is spotless "
		+ "hard wood, and the closet door is closed. Unlike the children's "
		+ "room, this one is free from clutter."
		+ "\n");
	
	add_prop(OBJ_S_SEARCH_FUN, "search_closet");
	
	add_walls();
	add_bedroom_master("large", "wood");
	add_window("green");
	remove_item("wall");
	add_item( ({"wall", "walls"}), "The walls are covered in wood panneling. "
		+ "On the south wall, directly across from the bed, you see a large "
		+ "painting.\n");
	add_item( "painting", "The painting is a completely black background with "
		+ "spatters of green paint across it (the green matches the curtains "
		+ "perfectly), and in the middle of the canvas is a large, golden "
		+ "pipe with grey smoke billowing out of it.\n");
	add_item( "south wall", "The south wall is covered in the same wood "
		+ "panneling as the other walls, but it has a painting on it.\n");
	add_exit(WAYM_HOUSE_DIR + "h_3_5", "west");	//Hallway

}

void
reset_shire_room()
{
	hat_pin = 1;
}

void
init()
{
	::init();

	
}

public string
search_closet(object me, string arg)
{
	object pin;
	
	
	if(arg != "closet")
	{
		return "";
	}
	if(hat_pin == 0)
	{
		return "";
	}
	pin = clone_object(WAYM_OBJ_DIR + "hat_pin");
	pin->move(TP);
	
	say(QCTNAME(TP) + " finds a hat pin on the floor in front of the closet!\n");
	hat_pin = 0;
	return("You find a hat pin on the floor in front of the closet!\n");
}
	