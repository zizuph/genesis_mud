/* File: /d/Shire/common/eastroad/eroad.9.c */ 

#define ROOM_NUMBER 9
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad to what looks like vast lands. "

        + "Looking northeast, you clearly get the picture of the Weather-hills, and "
        + "also an outstanding hill, which is called Weathertop by men. Elves call it "
        + "Amon Sul in their beautiful language. In the south, there is wilderland, "
        + "but far, far in the south, you can see the edges of the South Downs. "
        + "Closer to the north and northwest the horrible Midgewater Marshes extend. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.10", "east", 0);
    add_exit(TEMP_DIR + "eroad.8", "west", 0);
}
