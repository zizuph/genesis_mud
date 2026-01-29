/* File: /d/Shire/common/eastroad/eroad.23.c */

#define ROOM_NUMBER 23
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad east of Bree. Due south\n"+ 
         "you can see the Lone-lands stretching out. Far to the west\n"+
	 "you can see the the Weather Hills. The road continues \n"+
	 "eastwards just north of the Lone-lands.\n"	
	 );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.24", "east", 0);
    add_exit(TEMP_DIR + "eroad.22", "west", 0);
}
