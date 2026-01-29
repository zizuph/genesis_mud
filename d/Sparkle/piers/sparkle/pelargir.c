#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

public void
create_room()
{
    set_short("Berth 2 - Pelargir");
    set_long("Outside the pub.\n"+
      "Many sailors have drifted into oblivion here on the pier after" +
      " a hard time at the pub. A few of them have awakened without" +
      " a copper left in their pockets. Perhaps it would be better to" +
      " find a more suitable place to rest.\nThere is a sign here that" +
      " reads: Berth 2 - Pelargir.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit(S_LOCAL_ROOM_DIR + "ship_info", "north", 0);
    add_exit(S_LOCAL_ROOM_DIR + "pub",   "west",      0);
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/shire", "south",     0);
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/gont", "east",      0);

    add_item(({"pier" }), "It is one of the piers of the harbour where "
      + "ships can land so passengers can board or disembark and cargo "
      + "can be loaded or unloaded. Wooden planks lie on thick wooden "
      + "posts that reach down into the water. Other piers are south and "
      + "east of here.\n");
    add_item(({"water", "posts", }),
      "The water here in the harbour is murky and smells pretty bad. The "
      + "thick posts of the pier reach down into the water.\n");
    add_item(({"planks", "ground", "floor", }),
      "Wooden planks cover the ground here. They rest on thick posts "
      + "that reach down into the water of the harbour.\n");
    add_item(({"pub" }),"The pub is one of the most popular places in town.\n"+
      "If it's due to the low price of beer or just the rough atmosphere\n"+
      "is a matter yet to be settled. However, it can get quite crowded.\n"+
      "");
}

