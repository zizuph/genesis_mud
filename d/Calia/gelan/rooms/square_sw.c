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
    exits:      east and north to fountain, other to square

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

  set_short("Square south west");
  set_long("You are standing at a southwestern part of the town square "
          + "of Gelan. You are just southwest of the fountain that marks " 
          + "the square's centre, gushing crystal clear blue water. "
          +  "Going south, then west will take you to a house fully "
          + "overgrown with all kinds of plants and vegetables, the "
          + "grocery, and some way to the west is the smithy. "
          + "All around the square you can see "
          + "buildings of different shapes and colours. "
          + "Some way south you see the palace road that leads through the "
          + "town gate.\n");

  /* properties */

  add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

  add_exit(GELAN_ROOMS + "fountain_w","north",0);
  add_exit(GELAN_ROOMS + "square_southend_w","south",0);
  add_exit(GELAN_ROOMS + "square_corner_sw","west",0);
  add_exit(GELAN_ROOMS + "fountain_southend_w","east",0);
  add_exit(GELAN_ROOMS + "square_fountain_w","northwest",0);
  add_exit(GELAN_ROOMS + "square_southend_center_w","southeast",0);

  /* items in the room */

  add_square_items("blacksmith");
  add_square_items("gate_north");
  add_square_items("grocery");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */