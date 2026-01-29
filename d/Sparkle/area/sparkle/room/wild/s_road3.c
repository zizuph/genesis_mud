/* 	s_road3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void
create_room()
{
    set_short("Bright road");
    set_long("\n"+
             "Bright road.\n"+
             "To the north you can see the road leading away towards a village\n"+
             "while south there is nothing but wild terrain. You realize that\n"+
             "if you choose to go south to where the road vanishes over the crest\n"+
             "of a hill at the horizon, then you're in for quite a long walk.\n"+
             "");

    add_exit ("s_road2","north");
    add_exit(S_LINK_RPG_THEATRE, "west");

    add_item(({"road","village","terrain","crest","horizon","hill" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

