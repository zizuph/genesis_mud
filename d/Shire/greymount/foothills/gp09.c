/*
	*Path west of the Anduin, to the Grey Mountains
	*Altrus, September 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"

inherit GREY_DESC;
inherit GREY_BASE;

void create_path_room()
{
	set_vbfc_extra(path_desc1);
	
	add_foothills();
	add_gundabad_far();
	add_misty();
	add_grey_northwest();
	add_langwell_near();
	add_greylin_far();
	add_rtells();
	add_exit(FOOT_DIR + "gp06", "south");
	add_exit(FOOT_DIR + "gp10", "northwest");
	add_exit(FOOT_DIR + "gp11", "northeast", "@@wade_river@@");
	
	reset_shire_room();
}

void reset_shire_room()
{
}

int wade_river()
{
	write("You quickly wade through the rushing stream, the ice-cold water chilling you to the bone.\n");
	TP->add_fatigue(-20);
	return 0;
}
