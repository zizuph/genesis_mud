/* File: /d/Shire/common/eastroad/eroad.3.c */ 

#define ROOM_NUMBER 3
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going eastwards from Bree.\n"

        + "To the north you see the edges of the large forest called Chetwood, "
        + "and south of the road, the wilderness flourishes. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.4", "east", 0);
    add_exit(TEMP_DIR + "eroad.2", "west", 0);
}
