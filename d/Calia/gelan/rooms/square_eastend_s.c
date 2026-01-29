/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:
                29/8/95     description amended             Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                01.08.94    descriptions                    Deinonychus
                20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 3. 1.93    slight modifications            Merlin
                21.12.92    descs                           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      east to hairdresser, south to lavatory, n-nw-w-sw to square

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
  create_square_room();

    /* descriptions */

    set_short("Square eastend south");
    set_long("You are standing at the eastern edge of the town "
       + "square of Gelan, just north of a freshly painted blue building "
       + "(the public lavatory) and just west of a house in the shape of "
       + "a giant shampoo bottle (the hairdresser). To "
       + "the north and west the square streches out, with a great "
       + "fountain at its centre. All around the square you can see buildings "
       + "of different shapes and colours. "
       + "Far to the southwest you see the huge gate of Gelan.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_eastend","north",0);
    add_exit(GELAN_ROOMS + "lavatory","south",0);
    add_exit(GELAN_ROOMS + "square_fountain_e","west",0);
    add_exit(GELAN_ROOMS + "hairdresser","east",0);
    add_exit(GELAN_ROOMS + "square_e","northwest",0);
    add_exit(GELAN_ROOMS + "square_corner_se","southwest",0);

    /* items in the room */

    add_square_items("gate_north");
    add_square_items("lavatory");
    add_square_items("hairdresser");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */