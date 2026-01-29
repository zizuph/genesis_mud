/*
 *  /d/Sparkle/area/tutorial/castle/hallway_3s.c
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
    set_short("at the west end of a long hallway within the castle");
    set_long("The feeling of malevolence and dread is thick here at"
      + " the end of a long corridor which travels into the shadows"
      + " to the east. Though the torches along the walls provide"
      + " a kind of dim flickering light, they do nothing to cheer"
      + " these forsaken passages. North, it appears as if the"
      + " corridor meets with two other pathways.\n\n");

    add_item( ({ "north", "pathways", "other pathways",
                 "two pathways", "two other pathways" }),
        "North of here, the corridor appears to head both west and"
      + " south.\n");
    add_item( ({ "corridor", "long corridor" }),
        "The corridor travels into the shadows to the east.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_2s", "east");
    add_exit("hallway_4", "north");

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
