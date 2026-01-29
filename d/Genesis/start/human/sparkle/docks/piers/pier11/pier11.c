// /d/Genesis/start/human/town/pier11.c

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>                                                   

#include "../defs.h"

void
create_room()
{
    set_short("Berth 11, south pier");
    set_long("\n"+
        "You're at the east end of the south pier.\n"+
        "Looking east you see nothing but water.\n"+
             "");

    add_item(({"pier" }),"");            
    add_item(({"sign" }),
         "The sign has text which reads: " +
         "The Sgain Dubh to Port Macdunn in " +
         "Khalakhor.\n");
    add_cmd_item(({"sign"}), "read", 
         "The sign has text which reads: " +
         "The Sgain Dubh to Port Macdunn in " +
         "Khalakhor.\n");

    add_item(({"water" }),"The waves look foreboding. "+
    "You need a boat to go out there.\n"+
    "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_my_desc("There is a sign here marked 'Berth 11'\n");

    add_exit(TOWN_DIR + "pier10", "west");
}
