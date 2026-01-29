/*  /d/Faerun/sea/whalebones/rooms/beach1.c
*
*   By Nucifera, 2021
*
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_WHALEB_OUTDOOR;


void
create_whaleb_outdoor()
{
    extraline = "Walls of rock block flank you, this long winding path "
    +"appears to go in circles. you should consider turning back.";

    set_short("Your in a long winding mountain path");

    add_item(({"mountain", "cliff"}), "A large craggy clifface pierces th"
        +"rough clouds before you. Something feels off about it.");

    add_item(({"brush", "grass"}), "Not a glimer of greenerin in sight.");

    add_item(({"smell", "aroma", "air", "breeze"}), "The air here is clea"
         +"n and fresh, soothing a smile onto your face.");

    add_item(({"path", "trail"}), "The path lead nowhere, you feel you "
        +"should check back again later.");

    add_room_tell("The air in perfectly still and quiet, quite+
        +" stiflingly so.");

    add_room_tell("A dark cloud gathers around the mountain... you look "
        +"again and it's gone, a trick of wind perhaps?");

    add_exit(ROOM_DIR + "4o.c", "south");

    set_no_exit_msg( ({"north","northeast","northwest","east",
        "southeast", "southwest", "west"}),
        "There's nothing is nothing but rock in that directi"
        +"ction. Perhaps you should continue down the path.\n");

    reset_faerun_room();
}

void
reset_faerun_room()
{
    set_searched(0);
}
