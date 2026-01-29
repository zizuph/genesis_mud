/* File: /d/Shire/common/eastroad/eroad.11.c */ 

#define ROOM_NUMBER 11
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad from Bree.\n"

        + "This is a plain land, with a barren and stony landscape surrounding you in all "
        + "directions. Few trees live here, probably due to the harsh red soil here. "
        + "Only some small, stubborn trees clinch to whatever water they may find, though "
        + "in the northwest, there seems to be a growing amount of dense undergrowth. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.12", "east", 0);
    add_exit(TEMP_DIR + "eroad.10", "west", 0);
}
