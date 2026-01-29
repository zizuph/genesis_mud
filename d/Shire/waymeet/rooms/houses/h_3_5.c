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
#include "/d/Shire/waymeet/lib/hobbitmaker.h"


inherit WAYM_LIB_DIR + "base_hobbit_hole.c";
void add_hobbit();
object hobbit;

void reset_shire_room();

void
create_hobbit_room()
{
	set_short("In the East Hallway");
	
	set_long("This is a much quieter end of the house, away from all the "
		+ "clamour of the dining room and the clanging of pots and pans "
		+ "in the kitchen. The hallway leads to the bedrooms, children to "
		+ "to the north, and the parents to the east. But here, the "
		+ "wooden floors are clean, and the walls decorated with stenciled "
		+ "birds.\n");
	

	
	add_walls();
	remove_item("wall");
	add_item( ({"wall", "walls"}), "The walls are covered in wood panneling, "
		+ "just as in the rest of the house, but here they have been "
		+ "stenciled with robins and blue jays and mocking birds all "
		+ "flitting and flying around. They look happy and bright, "
		+ "just the kind of thing a small child would like to wake up "
		+ "to in the mornings.\n");
	add_item( ({"bird", "birds", "blue jay", "blue jays", "mocking bird", "mocking birds", "stencil", "stenciled"}),
		"The birds look like they're flying and singing all around the room. "
		+ "How cute!\n");
	add_item( ({"crow", "crows"}), "There are no crows here. This is a "
		+ "happy place.\n");

	add_exit(WAYM_HOUSE_DIR + "h_3_2", "west"); 	//Foyer	
	add_exit(WAYM_HOUSE_DIR + "h_3_6", "north");	//kid's bedroom
	add_exit(WAYM_HOUSE_DIR + "h_3_7", "east"); 	//master bedroom
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

add_hobbit()
{
	   if (!present(hobbit))
	   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(MILITA);
	hobbit->set_gender(0);
	hobbit->move(TO);
	int y =(random(3));
		if(!y)
			{
			object bracelet;
			bracelet = clone_object(WAYM_ARM_DIR + "h_bracelet");
			bracelet->move(hobbit);
			hobbit->command("wear bracelet");
			hobbit->command("smile soft");
			}
	   }
	   return ;
	
}