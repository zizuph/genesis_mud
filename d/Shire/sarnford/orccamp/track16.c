/*
 * Track in Evendim orc camp beyond the bushes
 * This track has no tents
 * By Finwe, May 2001
 */

#pragma strict_types

#include "local.h"
#include <macros.h>

inherit CAMP_BASE;

void
create_camp_room()
{
	set_extraline("A well worn track runs throughout the camp, " +
        "connecting this area with other parts of the camp. " +
        "The path turns east here as it goes beyond the rest of " +
        "the camp.");

	add_item(({"track","depression"}),"The track is a well worn" +
        "depression in the ground where countless feet have " +
        "passed by.\n");
    add_cmd_item("tent","enter","There are no tents to enter here.\n");
  
	add_exit(CAMP_DIR + "track15", "south");
	add_exit(CAMP_DIR + "track17", "east");


	reset_shire_room();
}

void reset_shire_room()
{
    clone_warning_orcs();
}

