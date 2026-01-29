/* File: /d/Shire/common/eastroad/eroad.20.c */

#define ROOM_NUMBER 20
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad east of Bree. South\n"+
	 "all that can be seen is the great marshes called Lone-lands. \n"+
	 "The road seems to go endlessly towards the east with \n"+
	 "only a small turn here and there. The land to the south \n"+
	 "seems wild and pathless, so you had better stick to the road.\n"
	 );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.21", "east", 0);
    add_exit(TEMP_DIR + "eroad.19", "west", 0);
}
