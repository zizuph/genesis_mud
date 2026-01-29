/*
 * Back yad for a farmhouse, outside Waymmet
 * Raymundo, March 2020
 */



#include "/d/Shire/sys/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Gondor/common/lib/herbsearch";


void
create_area_room()
{
    setuid(); 
    seteuid(getuid());

    area = "behind"; /* Distance from areaname */
    areaname = "a farmhouse";
    land = "the Shire";
    areatype = 1;
    areadesc = "back yard";
    
    extraline = "You stand on a well-maintained gravel path between the house "
		+ "and the curing shed. Short green grass lines each side of the "
		+ "path creating a cozy back yard. The yard is enclosed by a stone "
		+ "fence.";
	add_item("gravel", "The gravel is just crushed river rock.\n");
	add_item( ({"shed", "curing shed"}), "The curing shed is just south of "
		+ "here. It has been painted red and looks like the perfect place "
		+ "to keep tobacco until it's ready to be sold.\n");
	add_item( ({"house", "farmhouse"}), "To the north, you see the farmhouse. "
		+ "It's red, just like the shed, and in impeccable condition. There "
		+ "is a door to the north, leading back into the house.\n");
    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
   
    add_item(({"village", "Waymeet", "waymeet"}),
        "To the southeast you can see the small village of Waymeet.\n");

	add_item( ({"grass", "lawn"}), "The grass looks like it's been cut short. "
		+ "It's completely green with no brown spots whatsoever. Some hobbit "
		+ "has spent a lot of time keeping it just so!\n");
	add_item( ({"fence", "stone fence", "wall"}), "The fence is made of river "
		+ "rocks that have been mortared together. It looks like it would "
		+ "feel sturdy if you pushed it.\n");
	add_cmd_item( ({"fence", "stone fence", "wall"}), ({"push", "touch", "feel"}),
		"Yes indeed. The fence feels sturdy!\n");

	
	add_exit(WAYM_ROOM_DIR + "t_house", "north");
	add_exit(WAYM_ROOM_DIR + "t_shed", "south");
	
}

void
init()
{
	::init();
	add_action("do_climb", "climb");
	add_action("do_climb", "scale");
}

//can you climb the wall?
mixed
do_climb(string str)
{
	if(str == "wall" | str == "fence" | str == "rock wall" | str == "rock fence")
	{
	if(TP->query_skill(SS_CLIMB) >= (20 + random(20)))
	{
		write("You climb over the fence and back into the fields!\n");
		say(QCNAME(TP) + " climbs over the fence and back into the "
			+ "fields.\n");
		tell_room(WAYM_FIELD_DIR + "s_field12", QCNAME(TP) +
			" arrives, climbing over the fence.\n");
		TP->move_living("M", WAYM_FIELD_DIR + "s_field12", 0);
		return 1;
	}
	else
	{
		write("You try to climb the fence but fall on your butt!\n");
		say(QCNAME(TP) + " tries to climb the fence but falls on " 
			+ HIS_HER(TP) + " butt!\n");
		return 1;
	}
	}
	notify_fail("Climb what? The fence?\n");
	return 0;
	
}