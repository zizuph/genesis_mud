/* File: /d/Shire/common/eastroad/eroad.25.c */

#define ROOM_NUMBER 25
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long("You are walking on the Eastroad, far east of Bree. "
	    +"A forest is stretching out in front of you. It's "
	    +"called the Trollshaws. Rumours say that rock-trolls "
	    +"used to live there, way back in time. Southeast the "
	    +"Last bridge can be seen. There is an old shabby path "
	    +"leading northeast from here. ");

    add_item(({"eastroad", "road" }),
	"The road narrows a bit here, as you get closer to the bridge.\n");

    add_exit(TEMP_DIR + "eroad.26", "southeast", 0);
    add_exit(TEMP_DIR + "eroad.24", "west", 0);

}
