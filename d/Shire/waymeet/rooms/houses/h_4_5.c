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


void reset_shire_room();



void
create_hobbit_room()
{
	set_short("The End of the Hallway");
	
	set_long("The end of the hallway is, not coincidentally, the end of the "
		+ "hill. There is a window here on the west wall, as a result, making "
		+ "this quite a bright and airy feeling hallway, for a smial. A rug "
		+ "sits, thick and soft, between the children's bedroom to the "
		+ "north and the master bedroom to the south, allowing whomever "
		+ "needs to visit whomever in the night to do so without getting "
		+ "cold feet.\n");
	
	add_item("rug", "The rug is thick and soft. It's burgandy in color and "
		+ "stretches from room to room across the hallway. It looks like it'd "
		+ "be warm.\n");
	add_item("west wall", "The west wall is stuck up against the back end "
		+ "of the hill. It has a beautiful round window in it, allowing "
		+ "light in.\n");
		
	add_walls();
	add_window("green");

	add_exit(WAYM_HOUSE_DIR + "h_4_2", "east"); //Hallway
	add_exit(WAYM_HOUSE_DIR + "h_4_6", "north"); //Kid's room
	add_exit(WAYM_HOUSE_DIR + "h_4_7", "south"); //master bedroom

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
