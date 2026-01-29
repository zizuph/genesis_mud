/*
 * Track in Evendim orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"
#include <macros.h>

inherit CAMP_BASE;
inherit ENTER_BASE;

void
create_camp_room()
{
	set_extraline("A well worn track runs throughout the camp, " +
        "connecting this area with other parts of the camp. " +
        "Scattered about the camp are large tents. Occasionally " +
        "an orc enters or leaves a tent and eyes you suspiciously.");

	add_item(({"track","depression"}),"The track is a well worn" +
        "depression in the ground where countless feet have " +
        "passed by.\n");
  
	add_exit(CAMP_DIR + "track11", "north");
	add_exit(CAMP_DIR + "track04", "south");
	add_exit(CAMP_DIR + "track08", "east");
	add_exit(CAMP_DIR + "track06", "west");
	add_exit(CAMP_DIR + "track12", "northeast");
	add_exit(CAMP_DIR + "track10", "northwest");
	add_exit(CAMP_DIR + "track05", "southeast");

    set_tent_name("tent07");
	reset_shire_room();
}

void reset_shire_room()
{
    clone_warning_orcs();
}

