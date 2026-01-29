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
	set_vbfc_extra(path_desc2);
	
	add_foothills();
	add_misty_near();
	add_mirk_far();
	add_anduin_near();
	add_exit(FOOT_DIR + "fh08", "northeast");
	add_exit(FOOT_DIR + "fh06", "southwest");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


