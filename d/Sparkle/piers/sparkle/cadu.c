#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Berth 12 - Cadu");
    set_long("\n"+
      "You are at the east end of the south pier.\n" +
      "Looking east you see nothing but water.\nThere is a" +
      " sign here that reads: Berth 12 - Cadu.\n");

    add_item(({"pier" }),"");
    add_item(({"sign" }),
      "The sign has text which reads: " +
      "Passage to the island Nyreese and the town Cadu.\n");
    add_cmd_item(({"sign"}), "read",
      "The sign has text which reads: " +
      "Passage to the island Nyreese and the town Cadu.\n");

    add_item(({"water" }),"The waves look foreboding. "+
      "You need a boat to go out there.\n"+
      "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/macdunn", "west");
}

