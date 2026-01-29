/*
 *  /d/Sparkle/area/tutorial/castle/hallway_1s.c
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
public void        reset_room();


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("at the east end of a long hallway within the castle");
    set_long("Cold, torchlit walls run into the distance to the west,"
      + " where this wide corridor heads deeper into the castle. Dust"
      + " is deep in places along the carpet which, though elegant,"
      + " does little to cheer the malevolent atmosphere within the"
      + " castle. To the north, the entrance to the castle is"
      + " visible.\n\n");

    add_item( ({ "torchlit walls", "torchlit walls" }),
        "The walls are lined with sconces which contain torches that"
      + " illuminate the otherwise dark castle.\n");
    add_item( ({ "corridor", "hall", "hallway", "wide corridor",
                 "west" }),
        "The corridor travels further inside the castle to the west.\n");
    add_item( ({ "north", "entrance" }),
        "North of here, an entrance leads out of the castle.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_2s", "west");
    add_exit("entrance", "north");

    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void
reset_room()
{
    clone_guard(2);
} /* reset_room */
