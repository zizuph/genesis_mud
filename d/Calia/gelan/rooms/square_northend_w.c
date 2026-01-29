/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:
                31/5/96      call_outs taken out            Maniac
                07.01.95    removed block to post           Deinonychus
		11.09.94    inn opened			    Deinonychus
                    8.94    typos corrected                 Maniac 
    		15.12.93    items changed		    Deinonychus
    		21. 2.93    path system                     Merlin
       		21.12.92    descriptions		    Deinonychus
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      se to pillory, west to post, north to inn, ne to castle road
                e-se-s-sw to square

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
    set_short("Square northend west");
    set_long(
      "You're at the north end of the town square. To your " +
      "west you see the " +
      "Gelan post office, and the famous Calia inn is to your north. " +
      "Southeast is the pillory and when you're lucky you can " +
      "throw a tomato at some poor fellow there. All around the " +
      "square you see other interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "inn","north", 0);
    add_exit(GELAN_ROOMS + "square_nw","south",0);
    add_exit(GELAN_ROOMS + "post","west", 0);
    add_exit(GELAN_ROOMS + "square_northend_center_w","east",0);
    add_exit(GELAN_ROOMS + "castle_road_w1","northeast",0);
    add_exit(GELAN_ROOMS + "square_corner_nw","southwest",0);
    add_exit(GELAN_ROOMS + "pillory_w" ,"southeast",0);

    /* items in the room */

    add_item(({"post", "post office"}), DESC("post_office_house"));
    add_item(({"inn", "pub"}), DESC("inn_house"));
    add_item(({"sign"}), DESC("inn_sign"));
    add_item("pillory", DESC("pillory"));
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}),
             DESC("floor"));

} /* create_room */

/*
 * Function name: block_inn
 * Description:   don't let a player enter the inn
 * Arguments:     none
 * Returns:       1
 */
int block_inn()
{
  write(BS("Due to a scuffle in the inn, most of the interior is brocken. " +
    "The inn will open again as soon as everything's repaired.\n"));
  return 1;
}

/*
/*
 * Function name: block_post
 * Description:   don't let a player enter the post office
 * Arguments:     none
 * Returns:       1
 */
int block_post()
{
  write(BS("The post office is closed for restorations.\n"));
  return 1;
}
