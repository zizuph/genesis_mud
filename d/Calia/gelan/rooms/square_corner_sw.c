/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:  
                25/8/95     description modified            Maniac
                12.1.95     grocery block removed           Maniac
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
    exits:      west to alchemist, south to grocery, nw-n-e-se to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      doors to grocery and blacksmith
                blacksmiht door: has to be clean and black (polished and shining)
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

    set_short("Square corner south west");
    set_long("You are standing at the western edge of the town "
          + "square of Gelan. To the west is a blackened house with a " 
          + "large chimney, "
          + "the smithy. To the south you see the grocery, which is fully "
          + "overgrown with all kinds of plants and vegetables. "
          + "To the north "
          + "and east the square stretches out, with a great fountain "
          + "at its centre. All around the square you "
          + "can see buildings of different shapes and colours. "
          + "Far to the southeast you see the huge gate of Gelan.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_fountain_w","north",0);
    add_exit(GELAN_ROOMS + "grocery","south",0);
    add_exit(GELAN_ROOMS + "blacksmith","west",0); 
    add_exit(GELAN_ROOMS + "square_sw","east",0);
    add_exit(GELAN_ROOMS + "square_westend_s","northwest",0);
    add_exit(GELAN_ROOMS + "square_southend_w","southeast",0);

    /* items in the room */

    add_square_items("gate_north");
    add_square_items("grocery");
    add_square_items("blacksmith");


} /* create_room */
