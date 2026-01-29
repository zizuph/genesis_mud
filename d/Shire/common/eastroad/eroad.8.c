/* File: /d/Shire/common/eastroad/eroad.8.c */ 

#define ROOM_NUMBER 8
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad towards what seems to be a vast \n"

	+ "land. Looking northwards, only swamps and midgewater extends, and a well "
        + "suited name for the marshes it is indeed. South you can see the wilderland "
        + "in front of the far edges of the South Downs. The Great Eastroad turns "
        + "slightly here from the northwest to the east, probably because this is "
        + "the most southern point of the Midgewater Marshes. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.9", "east", 0);
    add_exit(TEMP_DIR + "eroad.7", "northwest", 0);
}
