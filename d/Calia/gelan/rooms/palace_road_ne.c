/* 	this is a room of the town Gelan

    coder(s):   Merlin, Deinonychus and Maniac

    history:
                24/8/95     description modified            Maniac
                17.07.94    descriptions                    Deinonychus
                18. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 2. 1.93    slight modifications            Merlin
                22.12.92    installed clean_up              Merlin
                21.12.92    descs                           Merlin
                21.12.92    installed door                  Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    road into town
    exits:      n-ne-nw to square, east to stables, s-sw-w to palace road

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

object door;                                    /* door in room */

public void
create_gelan_room()
{
    /* doors */

    door = clone_object(GELAN_DOORS + "palace_road_ne");
    door->move(this_object());

    /* descriptions */

    set_short("Palace road north east");
    set_long("You're standing on northeastern end of the palace road, "
          + "and can see the town square open out to your north. "
          + "To your east you see the bottom of a row of "
          + "huge columns that flank the road, creating a "
          + "corridor effect. They look so high that you can't "
          + "even see their tops! Behind the columns is one of the "
          + "stables of Gelan. "
          + "The palace road continues southwards, where it leads "
          + "to the drawbridge. The road is also wide, extending westwards "
          + "up to the columns that flank the other side of the gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_southend_center_e","north",0);
    add_exit(GELAN_ROOMS + "palace_road_se","south",0);
    add_exit(GELAN_ROOMS + "palace_road_nw","west",0);
    add_exit(GELAN_ROOMS + "square_southend_center_w","northwest",0);
    add_exit(GELAN_ROOMS + "square_southend_e","northeast",0);
    add_exit(GELAN_ROOMS + "palace_road_sw","southwest",0);

    /* items in the room */

    add_item(({"road","floor","ground"}), DESC("floor"));
    add_item(({"town","gelan","Gelan"}), DESC("gelan"));
    add_item(({"armoury", "armouries","house","building"}),
      DESC("armoury_house"));
    add_item("entrance", DESC("armoury_entrance"));
    add_item("sign", DESC("armoury_sign"));
    add_item(({"column","columns"}), DESC("gate_columns"));
    add_item("gate", DESC("gate"));
    add_item("square", DESC("square_far"));
    add_item("statue", DESC("fountain_statue_far"));
    add_item("marble", DESC("marble"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */