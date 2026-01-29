/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall2.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "pentagram_room";


/* Prototypes */
public void         create_pentagram_room();


/*
 * Function name:        create_pentagram_room
 * Description  :        constructor for the room
 */
public void
create_pentagram_room()
{
    set_side("southwest");
    set_extraline("A pile of corpses rests in the corner here.");

    add_item( ({ "corner" }),
        "The corner has been stacked with corpses.\n");
    add_item( ({ "corpse", "corpses", "pile", "pile of corpses" }),
        "The face of each of the dead is fixed with a twisted"
      + " expression of horror.\n");
    add_item( ({ "face", "faces", "faces of the dead",
                 "expression", "twisted expression",
                 "expression of horror",
                 "twisted expression of horror", "horror" }),
        "Not a pleasant sight.\n");
    add_item( ({ "pleasant sight" }),
        "That, it isn't.\n");
    add_item( ({ "southwestern end", "end" }),
        "Here, you stand at the point of a colossal pentagram that"
      + " is constructed of candles.\n");

    add_delay_cmd_item(
        ({ "corpse", "corpses", "pile", "pile of corpses" }),
        "search",
        "searching the pile of corpses",
        10,
        "You begin carefully searching the pile of corpses.\n",
        "Searching the corpses, you find further evidence that each"
      + " of these individuals died in a state of extreme terror. Their"
      + " hands are balled in tight fists, and the fingernails have"
      + " cut into the flesh of their palms.\n");

    add_exit("3_hall3", "north");
    add_exit("3_pit", "northeast", check_exit, 1, 0);
    add_exit("3_hall1", "east");

    set_no_exit_msg( ({ "southeast", "southwest", "south",
                        "northwest", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
