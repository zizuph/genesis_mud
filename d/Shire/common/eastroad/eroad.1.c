/* File: /d/Shire/common/eastroad/eroad.1.c */ 

#define ROOM_NUMBER 1
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going east from Bree.\n"

        + "Somewhat west you see a lonely house standing in this land. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
/*   add_exit(TEMP_DIR + "eroad.2","east",0); */
   add_exit(TEMP_DIR + "eroad.5","east",0,3);
    add_exit("/d/Shire/common/eastroad/forsaken" ,"west", 0);
}
