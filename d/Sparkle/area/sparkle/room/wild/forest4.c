/* 	forest4.c			Styles.   3 Mar 1993
 */

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void
create_room()
{
    set_short("Deep in a green forest");
    set_long("\n"+
             "In a forest.\n"+
             "This is a rueful place and you feel quite relaxed. The foliage high\n"+
             "above sways gently in the wind and allows a soft light to reach the\n"+
             "ground. A few birds can be heard but otherwise the forest is silent.\n"+
             "");

    add_exit("forest3","north");
    add_exit(S_LINK_MONK_MEADOWS, "west");

    add_item(({"ground","birds" }),
             "");
    add_item(({"forest" }),
             "The forest is very calm and there is a pleasant smell in the air.\n"+
             "");
    add_item(({"light" }),
             "The light gives this place a certain eerie feeling.\n"+
             "");
    add_item(({"foliage" }),
             "It sways gently in the wind.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

