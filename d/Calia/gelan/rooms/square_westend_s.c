/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:
                29/8/95     description modified            Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                01.08.94    descriptions                    Deinonychus
                21. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 3. 1.93    slight modifications            Merlin
                21.12.92    descs                           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      west to bank, south to blacksmith, rest to square

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


void
create_room()
{
  create_square_room();

    /* descriptions */

    set_short("Square westend south");
    set_long("You are standing at the western edge of the town square " 
          + "of Gelan, just north of a blackened house with a large " 
          + "chimney (the smithy), and just east of a cube shaped "
          + "sandstone building (the bank). "
          + "To the north and east the square stretches out, with "
          + "a great fountain at its centre. All around the square you "
          + "can see buildings of different shapes and colours. " 
          + "Far to the southeast you see the huge gate of Gelan.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_westend","north",0);
    add_exit(GELAN_ROOMS + "blacksmith","south",0);
    add_exit(GELAN_ROOMS + "bank","west",0);
    add_exit(GELAN_ROOMS + "square_fountain_w","east",0);
    add_exit(GELAN_ROOMS + "square_w","northeast",0);
    add_exit(GELAN_ROOMS + "square_corner_sw","southeast",0);

    /* items in the room */

    add_square_items("gate_north");
    add_square_items("blacksmith");
    add_square_items("bank");

/*
    set_alarm(1.0, 0.0, "reset_room");
*/

} /* create_room */
