/* File: /d/Shire/common/eastroad/eroad.17.c */

#define ROOM_NUMBER 17
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad east of Bree. Due "+
	 "west Weathertop is rising to its full height, reaching towards "+
	 "the sky. Eastwards there are vast, open lands as far as the eye "+
	 "can see. South the Lone-lands stretch out.\n"
	 );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.18", "northeast", 0);
/*  add_exit(TEMP_DIR + "eroad.16","southwest",0); */
    add_exit(TEMP_DIR + "eroad.13","southwest",0,4);
}
