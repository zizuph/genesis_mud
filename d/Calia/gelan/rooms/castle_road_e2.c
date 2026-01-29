/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                 6/4/99     temporary art gallery removed
                            descriptions added for road     Uhclem
                 6/4/99     connection to north road        Maniac
                31/5/96     call_outs taken out             Maniac
    		15.12.93    items changed                   Deinonychus
    		12. 2.93    guard/path system installed     Merlin
       		15.12.92    descriptions		    Deinonychus
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    road to castle
    exits:      north to castle (future), east to guards, w-sw-s to road

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
    set_short("castle road east");
    set_long("You're in the castle road. To your east are the " +
       "guards' headquarters which are currently closed to visitors. " +
       "There are more interesting buildings south and west of here, " +
       "and a gravel road leads north.\n");
    
	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "north_road_s1", "north", 0); 
    add_exit(GELAN_ROOMS + "castle_road_e1","south",0);
    add_exit(GELAN_ROOMS + "castle_road_w2","west",0);
    add_exit(GELAN_ROOMS + "guards_headquarter","east", "@@block");
    add_exit(GELAN_ROOMS + "castle_road_w1","southwest",0);

    /* items in the room */

    add_item(({"quarters", "headquarters", "guards' headquarters"}),
      DESC("police_house"));
    add_item(({"road","floor","ground","bottom"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));
    add_item(({"road", "gravel road"}),
        "The road is made of smooth gravel and promises easy " +
        "travel over otherwise difficult terrain.\n");
    add_item(({"gravel", "smooth gravel", "terrain", "surface",
        "difficult terrain"}),
        "The gravel is finely ground and hard packed, a comfortable " +
        "surface to walk on through terrain which is otherwise " +
        "quite craggy and uneven.\n");

} /* create_room */

/*
 * Function name: block
 * Description:   blocks a player
 * Arguments:     none
 * Returns:       1
 */
int block()
{
  write(BS("The guards' headquarters is closed to visitors.\n"));
  return 1;
}
