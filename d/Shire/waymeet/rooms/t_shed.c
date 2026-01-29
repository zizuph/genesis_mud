/* 
 *Farmhouse for Waymeet
 *
 * --Raymundo, Mar 2020
 */
 
inherit "/d/Shire/std/room";


#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

#define OUTSIDE "_i_can_go_out_back"
#define CRATE "_i_have_a_crate_already"
void reset_shire_room();


void
create_shire_room()
{
	set_long("The shed smells of curing tobacco. Strings of tobacco leaves hang "
		+ "from the rafters and walls, taking up nearly every available space "
		+ "in the barn. Looking up, you see large vents in the roof, which cause "
		+ "the air to circulate, drying the leaves. A small path has been left "
		+ "open down the center of the barn, allowing you to see the back wall.\n");
	set_short("Inside a Curing Shed");
	
	add_item( ({"wall", "walls", "north wall", "east wall", "west wall"}), 
		"Strings of hanging tobacco leaves block your view of the wall.\n");
	add_item( ({"south wall", "back wall"}), "Along the back wall, you notice "
		+ "crates of Pipeweed, ready for export.\n");
	add_item( ({"crate", "crates"}), "The crates are fairly large, but you could "
		+ "likely pick one up. They are wooden and on the side is painted:\n"
		+ "BEST QUALITY SHIRE PIPEWEED.\n");
	add_item( ({"roof", "ceiling"}), "Between the strings of pipweed, you see "
		+ "large vents, which enourage the air to circulate.\n");
	add_item( ({"string", "strings"}), "The strings hang from north to south all "
		+ "along the barn, from wall to wall, and rafters (nearly) to floor. "
		+ "There are tobacco leaves curing on the strings.\n");
	add_item( ({"leaf", "leaves", "tobacco", "tobacco leaves", "pipeweed"}),
		"The leaves are wrinkled and turning brown, a sign that they are curing "
		+ "nicely. When they are sufficiently cured, they will be packed in crates "
		+ "like the ones on the back wall and exported.\n");
	add_item("floor", "The floor is made of river stone. It's very clean, so as "
		+ "not to affect the quality of the Pipeweed.\n");

	add_prop(ROOM_I_INSIDE, 1);

	
	add_exit(WAYM_ROOM_DIR + "back_yard", "north", 0, 0, 1);
	add_exit(WAYM_ROOM_DIR + "back_yard", "out", 0, 0, 0);
	
		
}

void
reset_shire_room()
{

}

void
init()
{
	::init();
	add_action("do_get", "get");
	add_action("do_get", "pick");
	add_action("do_get", "take");
	add_action("do_get", "retrieve");
	
}

//Allows you to get the crate.
int
do_get(string str)
{
	if(str == "crate" | str == "up crate" | str == "crate up")
	{
		if(!TP->query_prop(OUTSIDE))
		{
			write("You need permission before you can pick up the crate. "
				+ "Go ask the farmer!\n");
			return 1;
		}
		if(TP->query_prop(CRATE))
		{
			write("You already got a crate!\n");
			return 1;
		}
		else
		{
			write("You pick up a crate of Pipeweed!\n");
			TP->add_prop(CRATE, 1);
			object crate;
			crate = clone_object(WAYM_OBJ_DIR + "tobacco_crate");
			crate->move(TP);
			say(QCTNAME(TP) + " picks up a " + crate->query_short() + ".\n");
			return 1;
		}
	}
	else
	{
		notify_fail("Pick up what? The crate?\n");
		return 0;
	}
}