/*
 *  /d/Sparkle/area/tutorial/castle/hallway_4.c
 *
 *  Within the castle of Baron von Krolock.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Prototypes */
public void        create_castle_room();


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("in one of the corridors within the castle");
    set_long("To the west, you feel a sense of growing dread, as if"
      + " some brooding force is bearing down on you. Looking in that"
      + " direction, you notice that the hallway narrows somewhat as"
      + " it travels deeper into the castle. North and south two"
      + " separate corridors travel to the east.\n\n");

    add_item( ({ "north", "south", "corridor", "corridors",
                 "long corridor", "long corridors", "corner" }),
        "Long corridors travel around a corner and head to the east"
      + " both north and south of this hallway.\n");
    add_item( ({ "hallway", "west" }),
        "The hallway appears to narrow to the west, where the sense"
      + " of dread grows more powerful.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_3n", "north");
    add_exit("hallway_5", "west");
    add_exit("castle_library", "east");
    add_exit("hallway_3s", "south");

    reset_room();
} /* create_castle_room */
