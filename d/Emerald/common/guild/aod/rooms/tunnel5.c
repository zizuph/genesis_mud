/*
 *  /d/Emerald/common/guild/aod/rooms/tunnel5.c
 *
 *  This is a connecting tunnel for the Army of Darkness guild.
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
    set_short("a long north-south tunnel");
    set_em_long("The ceiling of this long north-south tunnel towers"
      + " high above the ground. Clearly, this is a place meant"
      + " for the tallest race in Genesis - Ogrekind! To the south"
      + " the tunnel travels toward a large open chamber. North,"
      + " it continues to what appears to be a hall of some kind.\n");

    add_item( ({ "tunnel", "long tunnel", "north-south tunnel",
                 "long north-south tunnel" }),
        "The tunnel is enormous, and could easily allow ten men"
      + " walking abreast to pass by. It travels north and south.\n");
    add_item( ({ "chamber" }),
        "It looks large and open.\n");
    add_item( ({ "large chamber" }),
        "Yes, it is large ... large and open!\n");
    add_item( ({ "open chamber" }),
        "Yep ... its open alright. Pretty large too!\n");
    add_item( ({ "large open chamber",
                 "large and open chamber" }),
        "You can hardly ever remember seeing such a large and open"
      + " chamber. Its gotta be the largest opennest chamber that's"
      + " ever been large or open before.\n");
    add_item( ({ "hall" }),
        "It looks fairly official thataways.\n");
    add_item( ({ "official hall" }),
        "Yessiree ... official as all get out!\n");

    add_cave_items();
    add_spike("tunnel5");

    add_exit("council", "north");
    add_exit("bbroom", "south");
} /* create_cave_room */