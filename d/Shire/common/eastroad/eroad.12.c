/* File: /d/Shire/common/eastroad/eroad.12.c */ 

#define ROOM_NUMBER 12
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad from Bree.\n"

        + "In this plain land of Eriador, with small stunted trees and red soil, you notice "
        + "an outstanding top somewhat northeast of you. It must be the famous Amon Sul, "
        + "Weathertop in the language of men. Further north you see the Weatherhills "
        + "standing ridged and barren. Some bogs and small marshes are scattered between "
        + "you and the ridges, though this is perhaps just some small parts of the "
        + "Midgewater Marshes. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_exit(TEMP_DIR + "eroad.13", "east", 0);
    add_exit(TEMP_DIR + "eroad.11", "west", 0);
}
