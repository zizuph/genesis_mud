/* File: /d/Shire/common/eastroad/eroad.18.c */

#define ROOM_NUMBER 18
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad going east of Bree.\n"+
	 "To the west Weathertop rises to its full height, reaching "+
	 "towards the sky. The Lone-lands stretch out to "+
	 "the south. Far north some mountains stand, but it's hard "+
	 "to make out their size from this immense distance.\n");

    add_item(({"eastroad", "road" }),
	"The road is wide, stretching out eastwards. It seems to be in constant use. "
    );
    add_exit(TEMP_DIR + "eroad.19", "east", 0);
    add_exit(TEMP_DIR + "eroad.17", "southwest", 0);
}
