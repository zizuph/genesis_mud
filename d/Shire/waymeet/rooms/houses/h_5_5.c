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


void reset_shire_room();

void add_hobbit();
object hobbit;

void
create_hobbit_room()
{
	set_short("The Bedroom");
	
	set_long("This bedroom is quite small. There is a small single bed "
		+ "that takes up most of the room, its matress lumpy and worn "
		+ "with time. The nightstand looks rickety and unsteady, and "
		+ "even the curtains on the window look faded and old. Whoever "
		+ "lives here clearly does not have the ability or resources "
		+ "to do much more than clean. You notice that all of the clothes "
		+ "on the shelves look like they belong to an old woman.\n");
	
	
	
	add_floor_poor("small");
	add_bedroom_poor("single");
	add_window("faded pink");
	add_exit(WAYM_HOUSE_DIR + "h_5_2", "east");
	add_hobbit();

}

void
reset_shire_room()
{
	add_hobbit();	
}

void
init()
{
	::init();
	

}


void
add_hobbit()
{
	   if (!present(hobbit))
	   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(ELDER);
	hobbit->set_gender(1);
	hobbit->move(TO);
		int y =(random(3));
		if(!y)
			{
			object anklet;
			anklet = clone_object(WAYM_ARM_DIR + "h_anklet");
			anklet->move(hobbit);
			hobbit->command("wear anklet");
			hobbit->command("smile soft");
			}
	   }
	   return ;
	
}