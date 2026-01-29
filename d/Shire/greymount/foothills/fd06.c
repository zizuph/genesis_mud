/*
	*Field west of the Anduin, near foothills of the Misty Mountains
	*Altrus, June 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"

inherit FOOT_BASE;
inherit FIELD_BASE;

void create_field_room()
{
	set_vbfc_extra(field_desc1);
	
	add_foothills();
	add_misty_near();
	add_mirk_far();
	add_anduin_near();
	
	add_exit(FOOT_DIR + "fh04", "east");
	add_exit(FOOT_DIR + "fd07", "west");
	add_exit(FOOT_DIR + "fh05", "north");
	add_exit(FOOT_DIR + "fd03", "south");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


