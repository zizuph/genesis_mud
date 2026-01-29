/* File: /d/Shire/common/eastroad/eroad.6.c */ 

#define ROOM_NUMBER 6
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad from Bree, towards what seem\n"

	+ "to be unknown territories. Continuing northwest and southeast, the  "
	+ "Great Eastroad travels the boundaries of the famous Midgewater Marshes. "
	+ "You can hear the sounds of buzzing midges and small animals, most probably "
	+ "toads and frogs.\n"
    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.7", "southeast", 0);
    add_exit(TEMP_DIR + "eroad.5", "northwest", 0);
}
