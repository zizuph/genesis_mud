// /d/Genesis/start/human/town/pier10.c

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>                                                   

#include "../defs.h"

void
create_room()
{
    set_short("Berth 10, south pier");
    set_long("\n"+
      "You're near the east end of the south pier.\n"+
      "Looking east you see another berth before the pier ends "+
      "in nothing but water.\n"+
      "");

    add_item(({"pier" }),"");            
    add_item(({"sign" }),
      "The sign has text which reads: " +
      "Passage to the Lands of Ansalon.\n");
    add_cmd_item(({"sign"}), "read", 
      "The sign has text which reads: " +
      "Passage to the Lands of Ansalon.\n");

    add_item(({"water" }),"The waves looks foreboding. "+
      "You need a boat to go out there.\n"+
      "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_my_desc("There is a sign here marked 'Berth 10'\n");

    add_exit(TOWN_DIR + "parrot", "west");
    add_exit(TOWN_DIR + "pier11", "east");
}
