/*
 *  /d/Sparkle/area/tutorial/castle/hallway_6s.c
 *
 *  Within the Castle just north of Krolock's study.
 *
 *  Created October 2005, by Cooper Sherry (Gorboth)
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
    set_short("north of a study in the castle");
    set_long("You stand before a doorway leading south into what appears"
      + " to be a study. North, a narrow hallway leads"
      + " toward an intersection of passageways.\n\n");

    add_item( ({ "door", "doorway", "north", "wooden door",
                 "wooden doorway" }),
        "To the south, a wooden doorway opens onto what appears to be"
      + " a study.\n");
    add_item( ({ "hall", "hallway", "corridor", "south",
                 "narrow hallway" }),
        "The hallway travels a ways to the north, where it appears to"
      + " branch to the east and north.\n");
    add_item( ({ "study" }),
        "A study is through the doorway to the south. You can't"
      + " make out much detail from here.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_6", "north");
    add_exit("study", "south", &check_exit(
        "The massive demon guard steps in front of you, barring your"
      + " way into the study.\n"), 1, 0);

    set_trigger_room("study");
    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void
reset_room()
{
    clone_guard(1, "massive");
} /* reset_room */


