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
    extraline = "Coarse wirey grass and br"
    + "ush is scattered around the base of a steep craggy mountain to you"
    +"r north. Cool fresh"
    +" sea breeze tickles your senses. This windswept coastal plateau con"
    +"tinues on further inland in all directions.";

    set_short("A flat, elevated landform");

    add_item(({"plateau"}),"You stand on a rocky platau on Finback "
        +"Island.\n");

    add_item(({"mountain", "cliff"}), "A large craggy clifface pierces th"
        +"rough clouds to your southwest. Something feels off about it.\n");

    add_item(({"brush", "grass"}), "Dry scragly brush grabs at you"
        +"as you wade though it.\n");

    add_item(({"smell", "aroma", "air", "breeze"}), "The air here is clea"
         +"n and fresh, soothing a smile onto your face.\n");

    add_room_tell("You percieve a slight shift in the direction of the wi"
        +"nd.");

    add_room_tell("A dark cloud gathers around the mountain... you look "
        +"again and it's gone, a trick of wind perhaps?");

    add_exit(ROOM_DIR + "4o.c", "north");
    add_exit(ROOM_DIR + "5o.c", "northeast");
    add_exit(ROOM_DIR + "10o.c", "east");
    add_exit(ROOM_DIR + "14o.c", "southeast");
    add_exit(ROOM_DIR + "13o.c", "south");
    add_exit(ROOM_DIR + "12o.c", "southwest");
    add_exit(ROOM_DIR + "8o.c", "west");
    add_exit(ROOM_DIR + "3o.c", "northwest");

    reset_faerun_room();
}

void
reset_faerun_room()
{
    set_searched(0);
}
