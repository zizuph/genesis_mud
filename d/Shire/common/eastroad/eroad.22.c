/* File: /d/Shire/common/eastroad/eroad.22.c */

#define ROOM_NUMBER 22
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad east of Bree. Due south \n"+
	 "the Lone-lands can be seen stretching out. West the Weather \n"+
	 "Hills can be seen. The road continues eastwards. The Lone-lands \n"+
	 "is a very big vast land-area. It is not wise to get lost there. \n");

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.23", "east", 0);
    add_exit(TEMP_DIR + "eroad.21", "northwest", 0);
}
