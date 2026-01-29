/*
 *  /d/Sparkle/area/tutorial/castle/hallway_6n.c
 *
 *  Within the Castle just south of Krolocks bedchambers.
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
    set_short("south of some bedchambers in the castle");
    set_long("You stand before a doorway leading north into what appears"
      + " to be bedchambers of some kind. South, a narrow hallway leads"
      + " toward an intersection of passageways.\n\n");

    add_item( ({ "door", "doorway", "north", "wooden door",
                 "wooden doorway" }),
        "To the north, a wooden doorway opens onto what appears to be"
      + " bedchambers.\n");
    add_item( ({ "hall", "hallway", "corridor", "south",
                 "narrow hallway" }),
        "The hallway travels a ways to the south, where it appears to"
      + " branch to the east and south.\n");
    add_item( ({ "chamber", "bed", "bed chamber", "chambers",
                 "bed chambers", "bedchamber", "bedchambers" }),
        "The bedchambers are through the doorway to the north. You can't"
      + " make out much detail from here.\n");

    add_castle_items();
    add_torch_items();

    add_exit("bedroom", "north", &check_exit(
        "The massive demon guard steps in front of you, barring your"
      + " way into the bed chambers.\n"), 1, 0);
    add_exit("hallway_6", "south");

    set_trigger_room("bedroom");
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
