/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:
                25/8/95     description modified            Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                17.07.94    descriptions                    Deinonychus
                21. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 3. 1.93    slight modifications            Merlin
                21.12.92    descs                           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      east to bakery, sw sto palace road, other to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      door to bakery
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

    set_short("Square southend east");
    set_long("You are standing at the southeastern corner of the town "
          + "square of Gelan. To your east you see a little gingerbread "
          + "house. By the sign over the entrance you recognise it as the "
          + "McCroissant bakery. To the northeast you see a large, clean " 
          + "looking building, the public lavatory. To the north and west "
          + "the square stretches out. All around the square you can see "
          + "buildings of "
          + "different shapes and colours. To your northwest is a large "
          + "hexagonal shaped fountain, with a statue in it. Southwest "
          + "you see the palace road that leads through the town gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_se","north",0);
    add_exit(GELAN_ROOMS + "square_southend_center_e","west",0);
    add_exit(GELAN_ROOMS + "bakery","east",0);
    add_exit(GELAN_ROOMS + "square_corner_se","northeast",0);
    add_exit(GELAN_ROOMS + "palace_road_ne","southwest",0);

    /* items in the room */

    add_square_items("lavatory");
    add_square_items("gate_north");
    add_square_items("bakery_e");

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */