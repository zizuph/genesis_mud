/* Outdoors in Waymeet
 * Raymundo, Jan 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

inherit WAYM_LIB_DIR + "base_waymeet.c";




void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("This is a gentle curve in the street, which now "
		+ "runs from west to south. To the east you would find yourself "
		+ "deeper into Waymeet's residential neighborhood, while south "
		+ "moves you toward the Great East Road. A very quiet smial "
		+ "sits north of the road, its door shut tight and curtains "
		+ "drawn.\n");
		
	add_item( ({"smial", "hole", "hobbit hole", "house"}),
		"The smial is small, at least from the outside. The door is a "
		+ "bright shade of red, and the curtains in the window are "
		+ "green.\n");
	add_item( "door", "The door is red, and round, but the paint is "
		+ "chipped from knocking. It's shut tight.\n");
	add_cmd_item("on door", "knock", "@@do_knock@@");
	add_cmd_item("door", "open", "You try to open the door but it's "
		+ "locked.\n");
	add_cmd_item("door", "unlock", "You don't have the key (likely because "
		+ "this isn't your house.)\n");
	add_cmd_item("lock on door", "pick", "This lock is beyond your ability "
		+ "to pick.\n");
	add_item( ({"curtain", "curtains"}), "The curtains are a really cute "
		+ "shade of green. They're closed completely. You might be able "
		+ "to peek inside.\n");
	add_cmd_item("inside", "peek", "No, you can't peek inside. But now you "
		+ "look like some sort of peeping Tom because you tried to spy on "
		+ "whoever lives here.\n");
	add_cmd_item("window", "open", "The window is closed. You can't open it.\n");
	add_item("window", "The window is round and good-sized for a smial. There "
		+ "are green curtains in it, and they are closed.\n");
		


	add_street(1);
	
	
	
	add_exit(WAYM_STREET_DIR + "street_5", "south", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_3", "west", gravel_sound, 0, 0);
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

string
do_knock()
{
	int door_chance = (random(10));
	if(!door_chance)
	{
		say(QCTNAME(TP) + " knocks a little too hard on the door and some paint "
			+ "chips off and falls to the ground.\n");
		object paint;
		paint = clone_object(WAYM_OBJ_DIR + "paint_chip");
		paint->move(environment(TP));
		return("You knock a little too hard on the door and a piece of "
			+ "paint chips off and falls to the ground.\n");
	}
	else
	{
		return("You knock on the door, but you hear no answer from within.\n");
	}
}