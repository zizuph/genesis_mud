/*
    /d/Shire/waymeet/rooms/fields/field01.c

    Field in the farm north of Waymeet
    Perrigrine, February 2019
	
	added some trees and juniper berries for a task
	in the inn in Waymeet.
	Raymundo, Jan 2020
	
	for s_field* added tobacco for a task in the Cair Andros Basement
	Raymundo, March 2020
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

inherit WAYM_LIB_DIR + "base_field_south.c";

void reset_shire_room();

void create_field()
{
    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 4;
    areadesc = "tobacco field";

    extraline = my_extra();
	remove_item("house");
	add_item( ({"house", "farmhouse"}), "The farmhouse is painted red "
		+ "and has large windows that overlook the fields. The steps "
		+ "leading up to the door have been swept clean, and the door "
		+ "is open and inviting. A rock fence encloses what you infer "
		+ "is the back yard and curing shed.\n");
	remove_item("steps");
	add_item("steps", "The steps are made of oak. They have been varnished "
		+ "recently, and you don't even see any scuff marks on them.\n");
	add_item( ({"marks", "scuff marks", "mark", "scuff mark"}), "You don't "
		+ "see any scuff marks.\n");
	add_item( ({"fence", "wall", "rock fence", "rock wall"}),
		"The fence is made of river stones and looks sturdy.\n");
	add_item( ({"shed", "curing shed"}), "The curing shed peeks over the top "
		+ "of the fence. You notice that it's been painted red, and that there "
		+ "are large vents on the roof.\n");
	add_item("roof", "The roof is covered in shake shingles. You see large vents "
		+ "on it.\n");
	add_item( ({"shingle", "shingles"}), "The shingles are made of wood, which "
		+ "is not surprising given the number of trees in the Shire.\n");
	add_item( ({"vent", "vents"}), "The vents are large... but you can't quite "
		+ "tell what they're for. You'll need to get closer.\n");
		

    reset_shire_room();
	

   add_exit(WAYM_FIELD_DIR + "s_field11","east");
   add_exit(WAYM_ROOM_DIR + "t_house", "southwest");
   add_exit(WAYM_FIELD_DIR + "s_field08", "north");

}

void reset_shire_room()
{
  
}

void init()
{
    ::init();
	add_action("do_climb", "climb");
	add_action("do_climb", "scale");
  
}

int
do_climb(string str)
{
	if(str == "fence" | str == "wall" | str == "rock fence" | str == "rock wall")
	{
		if(TP->query_skill(SS_CLIMB) >= (20 + random(20)))
		{
		write("You climb over the fence and into the back yard.\n");
		say(QCTNAME(TP) + " climbs over the fence and into the back yard.\n");
		tell_room(WAYM_ROOM_DIR + "back_yard", QCTNAME(TP) + " arrives from over "
			+ "the fence.\n");
		TP->move_living("M", WAYM_ROOM_DIR + "back_yard");
		return 1;
		}
		else
		{
			write("You try to climb the fence but fall on your butt.\n");
			say(QCTNAME(TP) + " tries to climb the fence by falls on " 
				+ HIS_HER(TP) + " butt!\n");
			return 1;
		}
	}
	else
	{
		notify_fail("Climb what? The fence?\n");
		return 0;
	}
}
		
		
		