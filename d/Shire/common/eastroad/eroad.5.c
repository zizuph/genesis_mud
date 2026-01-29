/* File: /d/Shire/common/eastroad/eroad.5.c */ 

#define ROOM_NUMBER 5
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad from Bree to vast, unknown lands. "

        + "To the far northwest, you can see the edges of Chetwood, the large "
        + "forest northeast of Bree. Here the Great Eastroad turns to the "
        + "southeast, and you see why. Looking north and northeast a swampy "
        + "landscape meets your eye. These must be the famous Midgewater Marshes, "
        + "where you sure would not like to put your feet. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.6", "southeast", 0);
/*    add_exit(TEMP_DIR + "eroad.4","west",0); */
    add_exit(TEMP_DIR + "eroad.1","west",0,3);
}
