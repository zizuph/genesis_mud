/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:
                25/8/95     Description amended             Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                17.07.94    descriptions                    Deinonychus
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 3. 1.93    slight modifications            Merlin
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin
                21.12.92    descs                           Merlin

    purpose:    square
    exits:      north to fountain, south to palace road, other to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#include "room.h"
#pragma save_binary

inherit SQUARE_ROOM;
#include <stdproperties.h>

create_room()
{
    /* descriptions */

    create_square_room();

    set_short("Square southend center west");
    set_long("You are standing at the south end of the town square of "
          + "Gelan. Some way to your west you see the grocery, a house " 
          + "fully overgrown with plants and vegetables. To the " 
          + "north, west and east the square stretches out. All around the "
          + "square you can see buildings of different shapes and colours. "
          + "To your north is a large hexagonal shaped fountain with a "
          + "statue in it. South you see the palace road that leads through "
          + "the town gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "fountain_southend_w","north",0);
    add_exit(GELAN_ROOMS + "palace_road_nw","south",0);
    add_exit(GELAN_ROOMS + "square_southend_w","west",0);
    add_exit(GELAN_ROOMS + "square_southend_center_e","east",0);
    add_exit(GELAN_ROOMS + "square_sw","northwest",0);
    add_exit(GELAN_ROOMS + "palace_road_ne","southeast",0);

    /* items in the room */

    add_square_items("grocery");
    add_square_items("gate_north");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */