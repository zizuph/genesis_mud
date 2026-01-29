/* 
	*A lane leading to Maggot's farm and fields in the Marish
	*Altrus, March 2005
*/

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#define EAST_RD_DIR "/d/Shire/eastroad/western/"

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
	"a couple buildings to the west of here. Towards the east the " +
	"causeway dike can be seen.";
	
	add_item(({"hedge", "hedges"}), "The hedges are not very tall, no more than two feet high, but are very thickly leaved and dark green. They are well laid, bordering the lane on both sides.\n");
	add_item(({"fields"}), "Very orderly fields and meadows occupy the land; the farmers " +
	"around here tend their fields with care.\n");
	add_item(({"lane", "road", "path", "ruts"}), "It is rutted, most likely due to carts and " +
	"wagons passing through. Wild grass is growing between the ruts and on " +
	"either side of the lane.\n");
	add_item(({"buildings", "farmstead"}), "Looks like a quaint, one-story house and a " +
	"red barn for animal stalls and equipment storage. It must " +
	"be a farmstead.\n");
	add_item(({"house"}), "The house is only a single story and very short, " +
	"reminiscent of hobbit holes one might see in other areas of the Shire.");
	add_item(({"barn"}), "It is a faded-red, wooden structure, probably meant for " +
	"animal and equipment storage.");
	add_item(({"ground"}), "Here on the lane, the ground is hard packed dirt " +
	"and pebbles, with wild grass growing in spots.\n");
	add_item(({"wild grass", "grass"}), "It's just common grass growing on various " +
	"spots on the lane.\n");
	add_item(({"dike", "causeway", "the causeway"}), "It is a long dike, " +
	"running from the Stockbrook to Deephollow; it protects the fields of " +
	"the Marish from potential flooding of the Brandywine river further east.\n");
	
	set_room_tell_time(90);
	add_room_tell("A slight breeze blows across the fields.");
	add_room_tell("A thrush alights on the hedge.");
	add_room_tell("In the distance, a farmer can be heard yelling, " +
	"probably trying to chase off some birds landing in his field.");
	add_room_tell("Clouds pass by overhead, temporarily blocking " +
	"the sun.");
	
	add_exit(EAST_RD_DIR + "cause03", "east", "@@up_to_cause@@");
        add_exit(ROOM_DIR + "maggotlane02", "west");
        add_exit(EAST_RD_DIR + "cause03", "up", "@@up_to_cause@@",2,1 );

	
	reset_shire_room();
}

void reset_shire_room()
{
	
}
