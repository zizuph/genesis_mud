/* Outdoors in Waymeet
 * Raymundo, Jan 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit WAYM_LIB_DIR + "base_waymeet.c";



void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("Fields of vegetables have been planted past the smials "
		+ "to the west. You can access them by following the path. "
		+ "A little south of here is the Great East Road, "
		+ "which will take you either to Grey Havens or Bree. Further "
		+ "south still is the rest of Waymeet.\n");
	add_item("path", "The path leads west toward the fields.\n");
	add_smial("h_4_1");
	add_street(1);
	
	add_exit(WAYM_STREET_DIR + "street_2", "north", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_6", "east", gravel_sound, 0, 0);
	add_exit(WAYM_ROOM_DIR + "path_2", "west", 0,0,1);
	add_exit(WAYM_STREET_DIR + "street_7", "southeast", gravel_sound, 0, 0);
}
void
reset_shire_room()
{
	
}

void
init()
{
	::init();
	

}