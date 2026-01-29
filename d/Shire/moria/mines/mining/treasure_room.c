/* 
 * hidden chamber in Moria
 * Altrus, July 2005
 *
 * 2005/07/19 Last update
 * 2011/07/22 Lavellan - Made indoors and dark.
 * Dec 2017 Finwe, Made room non teleportable.
 */
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>

inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("A small dark chamber");

	set_long(short() + ". There is barely enough room to stand hunched " +
        "over in here. It is abyssmally dark, and very cold in here. " +
        "There are bits of junk littering the floor.\n");
	
	add_item(({"junk", "bits"}), "None of this junk looks particularly " +
        "useful or worth anything.\n");
	
	add_exit("/d/Shire/moria/mines/mining/dead_end", "south");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}
