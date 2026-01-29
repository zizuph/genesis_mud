/*
 *  /d/Emerald/common/guild/aod/rooms/pre_shop.c
 *
 *  This is the room that exists before the shop has been built.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
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
    set_short("in a mostly-empty chamber");
    set_em_long("You stand in a mostly empty chamber. A depression"
      + " in the east wall suggests that someone very strong has"
      + " been spending some time pounding on it. Aside from"
      + " a few debris, this room seems empty. It is hard to"
      + " tell what the function of this place is. Perhaps it"
      + " is being prepared for some future purpose.\n");

    add_item( ({ "chamber", "room", "here" }), long);
    add_item( ({ "purpose", "future purpose" }),
        "Its hard to know what this room might someday become.\n");
    add_item( ({ "big depression", "depression" }),
        "Looks like someone got mad at this wall!\n");
    add_item( ({ "eastern wall", "east wall" }),
        "A big depression has been beaten into the wall.\n");
    add_item( ({ "debris", "scattered debris" }),
        "It almost looks like someone was trying to build some"
      + " shelves or something - very unsuccessfully.\n");
    add_item( ({ "shelf", "shelves" }),
        "Um ... not even close. Looks more like a bad art project.\n");

    add_cave_items();
    add_spike("aod_shop");

    add_exit("tunnel4", "south");
} /* create_cave_room */