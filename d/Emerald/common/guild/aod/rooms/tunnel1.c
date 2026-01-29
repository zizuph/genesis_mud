/*
 *  /d/Emerald/common/guild/aod/rooms/tunnel1.c
 *
 *  This is a connecting tunnel in the Army of Darkness guildhall.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("at the north end of a long tunnel");
    set_em_long("Great billowing snores from the north nearly cause the"
      + " ground to shake here! This is the north end of a long"
      + " tunnel travelling southeast into the mountain.\n");

    add_item( ({ "snore", "snores", "great billowing snores",
                 "snoring" }),
        "It sounds as if a herd of congested rhinoceri are trying"
      + " to sleep in there.\n");
    add_item( ({ "ground" }),
        "It is vibrating slightly with all the ridiculous snoring"
      + " coming from the north.\n");
    add_item( ({ "tunnel", "long tunnel" }),
        "The tunnel is enormous, and could easily allow ten men"
      + " walking abreast to pass by. It travels to the southeast.\n");
    add_item( ({ "herd", "rhinoceri", "rhinocerous",
                 "congested rhinoceri", "herd of congested rhinoceri" }),
        "Its true. Sleeping ogres sound at least that bad.\n");

    add_cmd_item( ({ "snore", "snores", "great billowing snores",
                     "snoring" }),
                  ({ "listen" }),
        "It sounds as if a herd of congested rhinoceri are trying"
      + " to sleep in there.\n");

    add_cave_items();
    add_spike("tunnel1");

    add_exit("start", "north");
    add_exit("tunnel2", "southeast");
} /* create_cave_room */