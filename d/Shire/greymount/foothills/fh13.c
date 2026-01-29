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
	set_areadesc("crossing in a small river");
	set_area("in");
	set_areaname("the foothills");
	set_land("the Misty Mountains");
	set_areatype(0);
	extraline = "You are standing in a shallow portion of the river Rushdown. The water is cold, but only knee deep. Looming high overhead, the Misty Mountains dominate the view to the west. Mirkwood forest can be seen east of here.\n";
	
	add_item("water", "The ice cold water send shivers up your body. Better hurry up and cross the river.\n");
	add_item(({"river", "rivers"}), "There are two in the immediate area. The Langflood and the Rushdown, also known as Rhimdath.\n");
	add_item(({"small river", "rushdown", "rhimdath"}), "This is the river Rhimdath, also known as the Rushdown. It is small, compared to the larger Anduin, into which the Rushdown feeds.\n");
	add_item("langflood", "The river Langflood can be seen in the distance. The sound of it can be heard nearby as it rushes south to join the larger Anduin.\n");
	add_foothills();
	add_misty_near();
	add_mirk_near();
	
	add_exit(FOOT_DIR + "fh14", "northeast");
	add_exit(FOOT_DIR + "fh12", "south");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


