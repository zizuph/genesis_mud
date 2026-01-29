/*
	*Path west of the Anduin, to the Grey Mountains
	*Altrus, June 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"

inherit FOOT_BASE;
inherit AREA_ROOM;

void create_area_room()
{
	set_areadesc("bank");
	set_area("of a small river in");
	set_areaname("the foothills");
	set_land("the Misty Mountains");
	set_areatype(0);
	extraline = "The river, Rushdown, tumbles on its southeasterly course to join the Langflood. Looming high overhead, the Misty Mountains dominate the view to the west. Mirkwood forest can be seen east of here.\n";
	
	add_item(({"river", "rivers"}), "There are two in the immediate area. The Langflood and the Rushdown, also known as Rhimdath.\n");
	add_item(({"small river", "rushdown", "rhimdath"}), "This is the river Rhimdath, also known as the Rushdown. It is small, compared to the larger Anduin, into which the Rushdown feeds.\n");
	add_item("langflood", "The river Langflood can be seen in the distance. The sound of it can be heard nearby as it rushes south to join the larger Anduin.\n");
	add_foothills();
	add_misty_near();
	add_mirk_near();
	
	add_exit(FOOT_DIR + "fh15", "north");
	add_exit(FOOT_DIR + "fh13", "southwest");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


