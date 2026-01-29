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
	set_vbfc_extra(path_desc3);
	
	add_foothills();
	add_misty_near();
	add_mirk_near();
	add_anduin_near();
	add_rush();
	add_exit(FOOT_DIR + "fh12", "northwest");
	add_exit(FOOT_DIR + "fh10", "southeast");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


