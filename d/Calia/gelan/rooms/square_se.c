/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:
                25/8/95     description modified            Maniac
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
    exits:      west and north to founatin, rest to square

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

    set_short("Square south east");
    set_long("You are standing at a southeastern part of the town "
          + "square of Gelan. You are just southeast of the fountain " 
          + "that marks the square's centre, gushing crystal clear " 
          + "blue water. Going south, then east, will take you "
          + "to a little gingerbread house, the bakery, "
          + "and some way to the east is the public lavatory. "
          + "All around the square you can "
          + "see buildings of different shapes and colours. Some way south "
          + "you see the palace road that leads through the town gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "fountain_e","north",0);
    add_exit(GELAN_ROOMS + "square_southend_e","south",0);
    add_exit(GELAN_ROOMS + "fountain_southend_e","west",0);
    add_exit(GELAN_ROOMS + "square_corner_se","east",0);
    add_exit(GELAN_ROOMS + "square_fountain_e","northeast",0);
    add_exit(GELAN_ROOMS + "square_southend_center_e","southwest",0);

    /* items in the room */

  add_square_items("gate_north");
  add_square_items("bakery_e");
  add_square_items("lavatory");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
