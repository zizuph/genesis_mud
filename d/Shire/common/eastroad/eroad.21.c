/* File: /d/Shire/common/eastroad/eroad.21.c */

#define ROOM_NUMBER 21
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad east of Bree. Due south\n"+
	 "you can see the Lone-lands stretching out. To the west\n"+
	 "Weathertop can still be seen. The Weather Hills rise up a \n"+
	 "little north of it. Eastwards all that can be seen is vast,\n"+
	 "open land areas. The road continues eastwards towards the \n"+
	 "Last bridge, and westwards towards Bree.\n");

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.22", "southeast", 0);
    add_exit(TEMP_DIR + "eroad.20", "west", 0);
}
