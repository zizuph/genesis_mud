/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:
                 31/5/96    call_outs taken out             Maniac
                     9.94   typos corrected                 Maniac 
                 21. 2.93   path system                     Merlin
                 2.02.92    descriptions                    Deinonychus
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      west to shop, rest to square

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

    set_short("Square westend north");
    set_long("You're at the northern westend of the townsquare. To your " +
      "north you see the alchemist's house. Looking to the west you find " +
      "a really pompous shop. Maybe you can sell some stuff you don't need " +
      "for good money. There are other buildings all around the square.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_westend","south",0);
    add_exit(GELAN_ROOMS + "shop","west",0);
    add_exit(GELAN_ROOMS + "square_wn","east",0);
    add_exit(GELAN_ROOMS + "square_corner_nw","northeast",0);
    add_exit(GELAN_ROOMS + "square_w","southeast",0);

    /* items in the room */

    add_item(({"alchemist's house", "house"}), DESC("alchemist_house"));
    add_item("shop", DESC("shop_house"));
    add_item(({"floor", "ground", "bottom", "square"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));
    add_item(({"%", "%"}), BS("%\n"));

} /* create_room */

