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
	set_short("The Kitchen");
	
	set_long("You stand in the kitchen. It is much smaller than you would "
		+ "have imagined, given the size of the study across the hall, "
		+ "but perhaps that's because the hobbits also squeezed a dining "
		+ "room in east of here, so the two small rooms are about the "
		+ "size of one large one. Nevertheless, they have managed to get "
		+ "a tiny stove, some counters, a sink and an icebox in here. "
		+ "The pantry is tiny, but serviceable. This is a no-nonsense "
		+ "kitchen, but these being hobbits, you're sure it's still "
		+ "quite serviceable.\n");
	
		
	add_walls();
	add_stove("tiny");
	add_kitchen("oak");

	add_exit(WAYM_HOUSE_DIR + "h_4_2", "north"); //Hallway
	add_exit(WAYM_HOUSE_DIR + "h_4_8", "east"); //dining room


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
