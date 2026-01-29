#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Berth 11 - Port Macdunn");
    set_long("You are near the east end of the south pier.\n" +
      "Looking east you see another berth before the pier ends" +
      " in nothing but water.\n" +
      "There is a sign here that reads: Berth 11 - Port Macdunn.\n");

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

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/flotsam", "west");
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/cadu", "east");
}

