/* File: /d/Shire/common/eastroad/eroad.19.c */

#define ROOM_NUMBER 19
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad going east from Bree. South "+
	 "the great marshes called Lone-lands can be seen. You can't stop "+
	 "wondering why they are called the Lone-lands. To the southwest "+
	 "Weathertop can be seen, quite clearly actually. North of it, "+
	 "to the west, you can still see the Weather Hills. The road "+
	 "continues to the east and to the west.\n");

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.18", "west", 0);
/*    add_exit(TEMP_DIR + "eroad.20","east",0); */
   add_exit(TEMP_DIR + "eroad.24","east",0,4);
}
