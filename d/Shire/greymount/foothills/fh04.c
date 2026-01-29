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
	add_misty_close();
	add_mirk_far();
	add_anduin_near();
	add_exit(FOOT_DIR + "fh05", "northwest");
	add_exit(FOOT_DIR + "fh03", "south");
	add_exit(FOOT_DIR + "fd06", "west", 0, 3, 1);
	
	reset_shire_room();
}

void reset_shire_room()
{
}


