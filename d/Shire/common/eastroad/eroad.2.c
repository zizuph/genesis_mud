/* File: /d/Shire/common/eastroad/eroad.2.c */ 

#define ROOM_NUMBER 2
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going eastwards, towards\n"
	+  "unknown territories. Towards the north you see the edges of the large\n"
	+  "forest called Chetwood, and south of the road, the wilderness flourishes. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.3", "east", 0);
    add_exit(TEMP_DIR + "eroad.1", "west", 0);
}
