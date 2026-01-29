/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A low-income hobbit hole
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

void reset_shire_room();
//returns sun or moon for the long description

string
sun_moon()
{
	if(CLOCK->query_night())
	{
		return("moon");
	}
	else
	{
		return("sun");
	}
}
void
create_hobbit_room()
{
	set_short("In the Living Room");
	
	set_long("As you enter the smial, you notice immediately that the hobbits "
		+ "who live here are not well-to-do. Quite the opposite, infact. "
		+ "There is a threadbare rug on the floor. Very basic furniture "
		+ "lines the walls of what, in most smials, would be the foyer, but "
		+ "here is the main living space. There is a small window that lets "
		+ "in a little bit of " + "@@sun_moon@@" + "-light.\n");
	
	add_item( "furniture", "You see a sofa and a couple of chairs as furniture. "
		+ "They don't look very sturdy.\n");
	add_item( ({"sofa", "chair", "chairs"}), "It is made of wood. Instead of "
		+ "a cushion, there is a reed mesh to sit on. You're pretty sure it's "
		+ "not safe to sit on.\n");
	add_item( ({"reed", "reeds", "mesh", "reed mesh"}), "The reed mesh is "
		+ "just a bunch of reeds woven together in an effort to make them sturdy. "
		+ "In this case, you see several of the reeds are frayed, and you "
		+ "don't believe the mesh would support you.\n");
	add_item( ({"wall", "walls"}), "The walls are made of river rocks stacked "
		+ "one on top of another. They remind you of a cave.\n");
	add_item( "ceiling", "You can't say much about the ceiling, except that it "
		+ "keeps the rain off your head.\n");
	add_cmd_item( ({"chair", "chairs", "sofa", "in chair", "in chairs", "in sofa", "on chair", "on chairs", "on sofa"}), "sit", "You wouldn't dare sit on it! It'll break!\n");
	add_floor_poor("threadbare");
	add_window_two("small", "south");
	add_exit(WAYM_HOUSE_DIR + "h_2_2", "north"); //Bedroom (one for the family)
	add_exit(WAYM_HOUSE_DIR + "h_2_3", "east"); //kitchen and dining room
	add_exit(WAYM_STREET_DIR + "street_6", "out");
		
}

void
reset_shire_room()
{

}

void
init()
{
	::init();
	
}
