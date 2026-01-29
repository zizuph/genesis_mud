// /d/Genesis/start/human/town/pier10.c

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Berth 10 - Flotsam");
    set_long(
        "You walk along the south pier of Sparkle harbour.\n" +
        "The sea is lapping gently beneath you in rippling patterns.\n" +
        "There is a sign here that reads: Berth 10 - Flotsam.\n");

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

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/calia", "west");
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/macdunn", "east");
}

