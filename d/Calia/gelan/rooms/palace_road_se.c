/* 	this is a room of the town Gelan

    coder(s):   Merlin, Deinonychus & Maniac

    history:   
                24/8/95     description modified            Maniac
                21.09.94    descriptions                    Deinonychus
                14.9.94     blocking function to gse        Maniac
                17.07.94    descriptions                    Deinonychus
                26. 2.93    error removed                   Merlin
                18. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 2. 1.93    slight modifications            Merlin
                21.12.92    descs                           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    road into town
    exits:      n-ne-w to road, east to armoury, south to standby, sw to gate

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

public void
create_gelan_room()
{
    /* descriptions */

    set_short("Palace road south east");
    set_long("You're standing on the palace road in the town of "
          + "Gelan, which leads through the town's impressive gate. "
          + "To your east you see the bottom of a row of "
          + "huge columns that flank the road, creating a "
          + "corridor effect. They look so high that you can't "
          + "even see their tops! Behind the columns is one of the "
          + "armouries of Gelan, where town guardians dwell. "
          + "The palace road continues northwards, where a long way away "
          + "you can make out a town square with a glittering golden "
          + "statue. The road is also wide, extending westwards "
          + "up to the columns that flank the other side of the gate.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "palace_road_ne","north",0);
    add_exit(GELAN_ROOMS + "standby_guards","south",0);
    add_exit(GELAN_ROOMS + "palace_road_sw","west",0);
    add_exit(GELAN_ROOMS + "guards_armoury_se","east","@@gse_block");
    add_exit(GELAN_ROOMS + "palace_road_nw","northwest",0);
    add_exit(GELAN_ROOMS + "gate","southwest",0);

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


int
gse_block()
{
  write("The southeast guards armoury is currently off limits.\n");
  return 1;
}



/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */