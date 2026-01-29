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



void
create_hobbit_room()
{
	set_short("The Hallway");
	
	set_long("The hallway is short and nearly square. Standing on the rug, you "
		+ "can nearly touch all three doorways without moving your feet. "
		+ "To the south lies the kitchen. North is a sitting room, and west "
		+ "takes you to the bedroom. The only other noteworthy thing about "
		+ "the hallway is how clean it is, as if it's just been swept.\n");
	
	add_item( ({"doorway", "door way", "doorways", "door ways"}),
		"The doorways lead to the other rooms in the smial. They are small "
		+ "and painted a bright yellow, although the paint has started to "
		+ "chip. It seems whoever lives here hasn't repainted the doorways "
		+ "in quite some time.\n");
	
	add_floor_poor("clean but well-used");
	

	add_exit(WAYM_HOUSE_DIR + "h_5_1", "east");
	add_exit(WAYM_HOUSE_DIR + "h_5_3", "south"); //kitchen
	add_exit(WAYM_HOUSE_DIR + "h_5_4", "north"); //sitting room
	add_exit(WAYM_HOUSE_DIR + "h_5_5", "west"); //bedroom

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

