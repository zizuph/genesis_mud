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
#include "/d/Shire/waymeet/lib/hobbitmaker.h"

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

void add_hobbit();
object hobbit;

void
create_hobbit_room()
{
	set_short("In the Bedroom");
	
	set_long("The bedroom dim, despite the round window that lets in "
		+ "some light. You notice a lumpy bed taking up most of the room. "
		+ "There are some shelves along the wall and a pallet made up "
		+ "on the floor. A nightstand is next to the bed. Overall, the "
		+ "room looks quite spartan.\n");
		
	add_item("pallet", "The pallet is made up of blankets and a thin "
		+ "pillow. It appears to be a place for the children to sleep, "
		+ "while mom and dad sleep in the bed.\n");
	add_item("pillow", "The pillow is thin and greyish white. You notice "
		+ "two indentations in it, leading you to belive the pillow is "
		+ "shared between two children.\n");
		
	

	add_bedroom_poor("lumpy");

	add_floor_poor("thin");
	add_window_two("round", "west");
	add_exit(WAYM_HOUSE_DIR + "h_2_1", "south"); 
	
	add_hobbit();
}

void
reset_shire_room()
{
	if(!hobbit)
	{
		add_hobbit();
	}

}

void
init()
{
	::init();
	
}

void
add_hobbit()
{
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(ELDER);
	hobbit->set_gender(0);
	hobbit->move(TO);
	
}