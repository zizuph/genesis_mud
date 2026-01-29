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
    extraline = "Overlooking the southwestern bleakly inhospitable shore,"
    +" this windswept coastal plateau rises high above the bone"
    +"-littered beach bellow. Coarse wirey grass and br"
    + "ush scatter around the base of a steep craggy mountain to your nor"
    +"th. Cool fresh"
    +" sea breeze tickles your senses, absent of the acrid aroma of the "
    +"beach bellow.";

    set_short("A flat, elevated landform");

    add_item(({"sea", "ocean"}),"The view from here is breathtaking."
        +" Looking out across an endless canvas of blue with tufts of"
        +" gentle white soothes your soul. This must be what it feels "
        +"like to fly.\n");

    add_item(({"plateau"}),"You stand on a rocky platau on Finback "
        +"Island.\n");

    add_item(({"mountain", "cliff"}), "A large craggy clifface pierces th"
        +"rough clouds to your southwest. Something feels off about it.\n");

    add_item(({"brush", "grass"}), "Dry scragly brush grabs at you"
        +"as you wade though it.\n");

    add_item(({"smell", "aroma", "air", "breeze"}), "The air here is clea"
         +"n and fresh, soothing a smile onto your face.\n");

    add_item(({"bones", "litter","fragment", "fragments"}), "Fragments of"
         +" bones, shells and other various reffuse litter the beach far "
         +"below.\n");

    add_item(({"shore", "beach", "below"}), "You are standing on a platae"
        +"u on Finback Island, relieved to be away from the debris ridden"
        +"beach below you.\n");

    add_item(({"wave", "waves"}), "Briney white foaming waves ebb and flo"
        +"w, hauling debris further inland.\n");

    add_room_tell("A sudden gust of wind nearly propells you off the cliffs ed"
        +"ge");

    add_room_tell("A soothing melody of lapping waves fills you with a "
        +"sense of calm.");

    add_room_tell("You percieve a slight shift in the direction of the wi"
        +"nd, pushing you closer towards the cliffs edge.");

    add_room_tell("A dark cloud gathers around the mountain... you look "
        +"again and it's gone, a trick of wind perhaps?");

    add_exit(ROOM_DIR + "8o.c", "north");
    add_exit(ROOM_DIR + "9o.c", "northeast");
    add_exit(ROOM_DIR + "13o.c", "east");
    add_exit(ROOM_DIR + "7o.c", "northwest");

    set_no_exit_msg( ({"southeast", "south", "southwest", "west"}),
        "There's nothing in that directi"
        +"ction except thin air. You decide against it.\n");

    reset_faerun_room();
}

void
reset_faerun_room()
{
    set_searched(0);
}
