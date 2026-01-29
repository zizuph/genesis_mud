/* File: /d/Shire/common/eastroad/eroad.24.c */

#define ROOM_NUMBER 24
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are walking on the Eastroad from Bree. Due south\n"+
	 "the Lone-lands can be seen stretching out widely. Far to \n"+
	 "the west the Weather Hills can be seen. If you continue\n"+
	 "eastwards you will come to the Last bridge.\n"
	 );

    add_item(({"eastroad", "road" }),
	"The road is narrower here, about 2 meters, and seems to be in constant use.\n"
    );
/*  add_exit(TEMP_DIR + "eroad.23","west",0); */
   add_exit(TEMP_DIR + "eroad.25","east",0,3);
   add_exit(TEMP_DIR + "eroad.19","west",0,5);
}
