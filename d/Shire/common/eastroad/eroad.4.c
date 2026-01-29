/* File: /d/Shire/common/eastroad/eroad.4.c */ 

#define ROOM_NUMBER 4
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going west towards Bree,\n"
	+ "and east towards unknown territories. To the north you see the edges \n"
	+ "of the large forest called Chetwood, and south of the road, the \n"
	+ "wilderness flourishes. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.5", "east", 0);
    add_exit(TEMP_DIR + "eroad.3", "west", 0);
}
