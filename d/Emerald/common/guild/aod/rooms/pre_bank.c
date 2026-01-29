/*
 *  /d/Emerald/common/guild/aod/rooms/pre_bank.c
 *
 *  This is the room that exists before the bank has been built.
 *
 *  Created September 2006, by Cooper Sherry (Gorboth)
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
    set_short("in a dusty octagonal chamber");
    set_em_long("You stand in a chamber that appears to be awaiting"
      + " some future purpose. It has been excavated from the rock"
      + " with an octagonal perimeter. Aside from a few scattered"
      + " debris, the chamber appears empty.\n");

    add_item( ({ "chamber", "room", "here" }), long);
    add_item( ({ "purpose", "future purpose" }),
        "Its hard to know what this room might someday become.\n");
    add_item( ({ "perimeter", "octagonal perimeter", "wall",
                 "walls" }),
        "The perimeter of the room has been much more carefully"
      + " constructed than most things in these caves.\n");
    add_item( ({ "debris", "scattered debris" }),
        "Among the debris you notice a few gnome corpses, and some"
      + " strange device.\n");
    add_item( ({ "corpse", "corpses", "gnome", "gnome corpses",
                 "gnomes" }),
        "The gnomes look to have died painfully. Perhaps they"
      + " refused to share their trade secrets with the ogres.\n");
    add_item( ({ "device", "strange device", "abacus" }),
        "The device is an abacus, an ancient counting tool used by"
      + " gnomish bankers. Perhaps someday this room will be a"
      + " bank. I suppose the Harvest will need to secure more"
      + " gnome skulls first.\n");

    add_cave_items();
    add_spike("bank");

    add_exit("tunnel2", "west");
} /* create_cave_room */