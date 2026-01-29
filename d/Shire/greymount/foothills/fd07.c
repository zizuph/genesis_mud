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
	set_vbfc_extra(field_desc2);
	
	add_foothills();
	add_misty_near();
	add_mirk_far();
	add_anduin_far();
	
	add_exit(FOOT_DIR + "fd06", "east");
	add_exit(FOOT_DIR + "fd08", "west");
	add_exit(FOOT_DIR + "fd09", "north");
	add_exit(FOOT_DIR + "fd04", "south");
	
	reset_shire_room();
}

void reset_shire_room()
{
}


