/* 	this is a room of the town Gelan

    coder(s):   Merlin, Deinonychus & Maniac

    history:
                29/8/95     description amended             Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                01.08.94    descriptions                    Deinonychus
                20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 3. 1.93    slight modifications            Merlin
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin
                21.12.92    descs                           Merlin

    purpose:    square
    exits:      east to fountain, ne-n-nw-w-s-se to square

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

    set_short("Square fountain west");
    set_long("You are standing at a western part of the town square "
          + "of Gelan. You are just west of the fountain "
          + "that marks the square's centre, gushing crystal clear blue "
          + "water. Some way to your west is the bank, and the grocery is "
          + "some distance south, while going south then west from here will "
          + "take you to the smithy. All around the square you can see "
          + "buildings of different shapes and colours. "
          + "Some way southeast you see the palace road that leads "
          + "through the town gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_w","north",0);
    add_exit(GELAN_ROOMS + "square_corner_sw","south",0);
    add_exit(GELAN_ROOMS + "square_westend_s","west",0);
    add_exit(GELAN_ROOMS + "fountain_w","east",0);
    add_exit(GELAN_ROOMS + "square_westend","northwest",0);
    add_exit(GELAN_ROOMS + "square_fountain_nw","northeast",0);
    add_exit(GELAN_ROOMS + "square_sw","southeast",0);

    /* items in the room */

    add_square_items("gate_north");
    add_square_items("blacksmith");
    add_square_items("bank");
    add_square_items("grocery");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */