/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:     
                24/8/95     description modified            Maniac
                21.09.94    description                     Deinonychus
                 7.9.94     ga_sw blocked off until descs   Maniac
		17.07.94    descriptions		    Deinonychus
		18. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 2. 1.93    slight modifications            Merlin
                21.12.92    modified descs                  Merlin
                21.12.92    removed door                    Merlin
                29.11.92    included descs                  Deinonychus
                29.11.92    installed door                  Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    road into town
    exits:      n-ne-e to palace road, west to armoury, south to gate, sw to
                standby guards

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

    set_short("Palace road south west");
    set_long("You're standing on the palace road in the town of "
          + "Gelan, which leads through the town's impressive gate. " 
          + "To your west you see the bottom of a row of "
          + "huge columns that flank the road, creating a " 
          + "corridor effect. They look so high that you can't " 
          + "even see their tops! Behind the columns is one of the "
          + "armouries of Gelan, where town guardians dwell. " 
          + "The palace road continues northwards, where a long way away " 
          + "you can make out a town square with a glittering golden " 
          + "statue. The road is also wide, extending eastwards "
          + "up to the columns that flank the other side of the gate.\n"); 

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "palace_road_nw","north",0);
    add_exit(GELAN_ROOMS + "gate","south",0);
    add_exit(GELAN_ROOMS + "guards_armoury_sw","west","@@block_asw");
    add_exit(GELAN_ROOMS + "palace_road_se","east",0);
    add_exit(GELAN_ROOMS + "palace_road_ne","northeast",0);
    add_exit(GELAN_ROOMS + "standby_guards","southeast",0);

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



int block_asw()
{
  write("The southwest guards armoury is currently off limits.\n");
  return 1;
}
