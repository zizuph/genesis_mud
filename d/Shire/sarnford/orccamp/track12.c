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
  
	add_exit(CAMP_DIR + "track14", "north");
	add_exit(CAMP_DIR + "track08", "south");
	add_exit(CAMP_DIR + "track13", "east");
	add_exit(CAMP_DIR + "track11", "west");
	add_exit(CAMP_DIR + "track09", "southeast");
	add_exit(CAMP_DIR + "track07", "southwest");

    set_tent_name("tent12");
	reset_shire_room();
}

void reset_shire_room()
{
    clone_warning_orcs();

}

