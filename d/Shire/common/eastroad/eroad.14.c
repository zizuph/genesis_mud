/* File: /d/Shire/common/eastroad/eroad.14.c */ 

#define ROOM_NUMBER 14
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad east of Bree.\n"

        + "Now you are standing pretty close to a large top, the Weathertop. It stretches "
        + "above you in the north, and you would guess that anyone standing on the top "
        + "can see you here on the road. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.15", "northeast", 0);
    add_exit(TEMP_DIR + "eroad.13", "southwest", 0);
}
