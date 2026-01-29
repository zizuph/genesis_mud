/*
 *	/d/Gondor/ithilien/poros/pier.c
 *
 *	Modification log:
 *	20-Jan-97, Olorin: ROOM_I_NO_CLEANUP
 *	 3-Feb-97, Olorin: Changed inheritance.
 *  26-May-09, Tapakah: connected the second pier.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

inherit "/d/Genesis/gsl_ships/lib/pier";

public void    reset_room();

static object  Ship;

public void
create_gondor()
{
    set_short("a run-down pier reaching out into the Poros");
    set_long(BSN("This is an old run-down pier on the River Poros "
      + "on the border between Ithilien and South Gondor. Even though "
      + "the area is deserted, there are signs that not too long ago "
      + "a ship has docked here. Northeast of the pier are the fords "
      + "of Poros which prevent river traffic going farther upriver."));

    add_exit(ITH_DIR + "poros/ford_north", "northeast", 0, 2);
    add_exit(ITH_DIR + "poros/pier2", "southwest", 0, 2);

    add_item(({"pier", "dock"}), BSN(
        "This pier reaches out into the river Poros. It is in a rather "
      + "poor condition but it looks like a ship docked here not too "
      + "long ago."));
    add_item(({"river", "poros", "river poros", }), BSN(
        "The river Poros is the southern border of Ithilien. On the "
      + "other bank lies South Gondor which is now debatable and "
      + "desert land. To the northeast the ancient Harad road is "
      + "crossing the river on the fords of Poros. The river is "
      + "running down from the southern mountains of the Ephel Duath "
      + "visible to the east to the Ethir Anduin in the west."));
    add_item(({"road", "harad road", "ford", "fords", "fords of poros", }),
        BSN("Northeast of here are the fords of Poros, blocking "
      + "any river traffic from going any farther upriver. The ancient "
      + "trade road from Gondor to Harad, the Harad road is crossing "
      + "the Poros at these fords."));
    add_item(({"mountains", "ephel duath", "east", }), BSN(
        "The southern ranges of the Ephel Duath, the Mountains of Shadow "
      + "that are the western border of the land of Mordor, are rising "
      + "in the east. The river Poros is coming down from these mountains, "
      + "flowing rapidly to the Mouths of the Anduin in the west."));
    add_item(({"ethir anduin", "mouths of the anduin", "anduin", }), BSN(
        "To the west lie the Ethir Anduin, the Mouths of the Anduin, "
      + "where the river Anduin enter the Bay of Belfalas. The river "
      + "Poros is flowing there, so any ships travelling from the pier "
      + "here will go to the Anduin."));

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_pier_entry(MASTER_OB(TO), "Poros", "Line to Pelargir and Tharbad");
    initialize_pier();
    reset_room();
}

public void
reset_room()
{
  ::reset_room();
  return;
   if (!objectp(Ship))
   {
      Ship = clone_object(SHIP_DIR + "ship6");
      Ship->start_ship();
   }
   if (!present("sign", TO))
      clone_object(SHIP_DIR + "poros_sign")->move(TO);
}
