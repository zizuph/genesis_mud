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
    exits:      west to fountain, se to lavatory, all other to square

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

    set_short("Square fountain east");
    set_long("You are standing at an eastern part of the town square "
          + "of Gelan. You are just east of the fountain "
          + "that marks the square's centre, gushing crystal clear blue "
          + "water. Some way to your east is the hairdresser, and the bakery "
          + "lies some distance south, while going southeast from here will "
          + "take you to the public lavatory. All around the square you "
          + "can see buildings of different shapes and colours. "
          + "Some way southwest you see the palace road that leads "
          + "through the town gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_e","north",0);
    add_exit(GELAN_ROOMS + "square_corner_se","south",0);
    add_exit(GELAN_ROOMS + "fountain_e","west",0);
    add_exit(GELAN_ROOMS + "square_eastend_s","east",0);
    add_exit(GELAN_ROOMS + "square_fountain_ne","northwest",0);
    add_exit(GELAN_ROOMS + "square_eastend","northeast",0);
    add_exit(GELAN_ROOMS + "square_se","southwest",0);
    add_exit(GELAN_ROOMS + "lavatory","southeast",0);

    /* items in the room */

    add_square_items("gate_north");
    add_square_items("lavatory");
    add_square_items("bakery_e");
    add_square_items("hairdresser");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */