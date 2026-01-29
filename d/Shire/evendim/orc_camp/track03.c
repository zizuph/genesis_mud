/*
 * Path in Evendim orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit CAMP_BASE;

void
create_camp_room()
{
	set_short("Outside a large tent");
	set_extraline("The grass is well trodden here by what looks " +
		"to be countless feet. A faint depression in the " +
		"ground runs west and northeast.");
	add_item(({"expanse","debris","litter"}),
		"The litter is mostly brush and other formerly living "+
		"debris, including not a few bones.\n");
	add_item(({"track","depression"}),"The track is little more than a "+
		"depression in the grass where countless feet have passed.\n");
  
	add_exit(CAMP_DIR + "track02", "west");
	add_exit(CAMP_DIR + "track04", "northeast", "@@block_way@@");

	reset_shire_room();
}

void reset_shire_room()
{
	clone_invading_orcs();
}
