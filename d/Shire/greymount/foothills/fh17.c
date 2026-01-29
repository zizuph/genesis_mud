/*
	*Path west of the Anduin, to the Grey Mountains
	*Altrus, June 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"

inherit FOOT_BASE;
inherit PATH_BASE;

void create_path_room()
{
	set_vbfc_extra(path_desc4);
	
	add_foothills();
	add_misty_far();
	add_mirk_near();
	add_lang_near();
	add_rush();
	add_exit(FOOT_DIR + "fh18", "north");
	add_exit(FOOT_DIR + "fh16", "south");
	add_exit(FOOT_DIR + "gp01", "northwest");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


