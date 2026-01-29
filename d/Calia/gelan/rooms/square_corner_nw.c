/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:     31/5/96     removed call_outs               Maniac  
                 24.3.95     removed block to alchemist      Maniac 
    		07.01.95    removed block to post           Deinonychus
                16.12.93    items changed		    Deinonychus
    		20. 2.93    path system                     Merlin
                10.01.92    descriptions                    Deinonychus
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      west to alchemist, north to post, ne-e-se-s-sw to square

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
    set_short("Square corner north west");
    set_long(
      "You're in the northwest corner of the town square. To your west " +
      "you see the house of the infamous alchemist Raspatoon Goldiloon, " +
      "a solid hemispherical " +
      "shaped building with star shaped windows. " +
      "North of you lies the post office, " +
      "maybe there's a letter from one of your friends waiting for " +
      "you there. There are other interesting buildings all around " +
      "the square.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);     /* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "post","north",0);
    add_exit(GELAN_ROOMS + "square_wn","south",0);
    add_exit(GELAN_ROOMS + "alchemist","west",0);
    add_exit(GELAN_ROOMS + "square_nw","east",0);
    add_exit(GELAN_ROOMS + "square_northend_w","northeast",0);
    add_exit(GELAN_ROOMS + "square_westend_n","southwest",0);
    add_exit(GELAN_ROOMS + "square_midw","southeast",0);

    /* items in the room */

    add_item(({"post", "post office"}), DESC("post_office_house"));
    add_item(({"alchemist's house", "house"}), DESC("alchemist_house"));
    add_item(({"window", "windows"}), "The windows are star-shaped, " +
             "and their panes consist of one-way mirrors in order that " +
             "nobody can " +
             "can watch Raspatoon working on his top-secret brews. On " +
             "one window is an inscription.\n");
    add_item(({"inscription"}), DESC("alchemist_inscription"));
    add_cmd_item(({"inscription"}), "read", DESC("alchemist_inscription"));
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));

} /* create_room */

