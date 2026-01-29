/* File: /d/Shire/common/eastroad/eroad.10.c */ 

#define ROOM_NUMBER 10
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going eastwards to unknown lands. "

        + "You have entered the southeastern edge of a swampy wetland called Midgewater "
        + "Marshes by men. A true name indeed, when noticing the midges humming around "
        + "you. If you follow the Road eastwards, you will get out of this itchy land. "
        + "While talking east; a top rises in the northeast, called Weathertop. "
        + "Lonesome it stands there, by the edge of the mountain range that is called "
        + "the Weather Hills. It looks like the Eastroad will end up just beneath the "
        + "southern foot of Weathertop. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.11", "east", 0);
    add_exit(TEMP_DIR + "eroad.9", "west", 0);
}
