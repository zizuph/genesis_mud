/* File: /d/Shire/common/eastroad/eroad.7.c */ 

#define ROOM_NUMBER 7
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad from Bree, towards undiscovered land. "

        + "Still the Midgewater Marshes lie to the north of you, forcing the Great Eastroad "
        + "to take a more southernly route than necessary. South of you there is "
        + "wilderland, though on the far horizon you can spot the edges of the "
        + "South Downs. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.8", "southeast", 0);
    add_exit(TEMP_DIR + "eroad.6", "northwest", 0);
}
