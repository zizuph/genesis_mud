// revision of /d/Genesis/start/human/town/parrot.c

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>                                                   

#include "../defs.h"

void
create_room()
{
    set_short("Berth 9, south pier");
    set_long("\n"+
        "You walk along the south pier of Sparkle harbour.\n"+
        "The sea is lapping gently beneath you in rippling patterns.\n"); 

    add_item(({"pier" }),"");            
    add_item(({"sign" }),"The sign has text which reads: " +
                         "Passage to the Lands of Calia.\n");
    add_item(({"sea", "water", "waves" }),
              "You know, that watery stuff that drips everywhere. " +
              "There seems to be a lot of it around here. This variety " +
              "is salty too.\n"); 

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_my_desc("There is a sign here marked 'Berth 9'\n");

    add_exit(TOWN_DIR + "pier8", "west");
    add_exit(TOWN_DIR + "pier10", "east");
}

