/* 	orc_road1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Orc road");
    set_long("\n"+
             "Orc road.\n"+
             "You are traveling down Orc road. It isn't as bad as the name implies\n"+
             "and the face of nature smiles at you. A lane leads up the hill to the\n"+
             "south and disappears out of sight at the top. Looking west you see\n"+
             "the entrance of a valley and some trees. East you see a crossing\n"+
             "and beyond lies the village of Sparkle.\n"+
             "");

    add_exit ("orc_road2","west");
    add_exit ("lane","south");
    add_exit ("crossroad","east");

    add_item(({"road","lane","hill","crossing","trees" }),
             "");
    add_item(({"village","Sparkle","sparkle" }),
             "Ah, Sparkle. A most legendary village. The origin of the human race.\n"+
             "");
    add_item(({"entrance","valley" }),
             "You see nothing special about the entrance to the valley.\n"+
             "");
    add_item(({"face" }),
             "What face? Your own? It's as ugly as ever.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

