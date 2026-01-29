
/* 
	*A lane leading to Maggot's turnip field in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";

public void
create_area_room()
{
	areadesc = "rutted lane";
	area = "somewhere in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	
	extraline = "The lane is bordered by low hedges. Everywhere " +
	"you look you see well-tended fields, evidence of the " +
	"skilled farmers that inhabit the area. There appears to be " +
	"a couple buildings to the east of here. To the west a rather large " +
	"turnip field is very near.";
	
	add_item(({"hedge", "hedges"}), "The hedges are not very tall, no more than two feet high, but are very thickly leaved and dark green. They are well laid, bordering the lane on both sides.\n");
	add_item(({"fields"}), "Very orderly fields and meadows, the " +
	"farmers around here tend their fields with care. In particular, " +
	"there is a large turnip field to the west\n");
	add_item(({"field", "turnip field"}), "Large does not begin to " +
	"describe this turnip field.\n");
	add_item(({"lane", "road", "path", "ruts"}), "It is rutted, most " +
	"likely due to carts and wagons passing through. Wild grass is " +
	"growing between the ruts and on either side of the lane.\n");
	add_item(({"buildings", "farmstead"}), "Looks like a quaint, " +
	"one-story house and a red barn for animal stalls and equipment " +
	"storage. It must be a farmstead. Sounds of activity can be heard " +
	"nearby.\n");
	add_item(({"house"}), "The house is only a single story and very " +
	"short, reminiscent of hobbit holes one might see in other areas " +
	"of the Shire. From here it looks very clean and orderly.\n");
	add_item(({"barn"}), "It is a faded-red, wooden structure, probably " +
	"meant for animal and equipment storage.\n");
	add_item(({"ground"}), "Here on the lane, the ground is hard " +
	"packed dirt and pebbles, with wild grass growing in spots.\n");
	add_item(({"wild grass", "grass"}), "It's just common grass growing on " +
	"various spots on the lane.\n");
	
	set_room_tell_time(90);
	add_room_tell("A slight breeze blows across the fields.");
	add_room_tell("A few crows, disturbed by something, suddenly " +
	"take flight.");
	add_room_tell("Clouds pass by overhead, temporarily blocking " +
	"the sun.");
	add_room_tell("Nearby, a dog starts barking loudly.");
	
	add_exit(ROOM_DIR + "maggotlane04", "east");
	add_exit(FIELD_DIR + "maggotfield07", "west");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}
