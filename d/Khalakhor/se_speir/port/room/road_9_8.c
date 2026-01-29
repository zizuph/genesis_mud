/*
 * The pier road running north off the piers past the
 * bladesmith forge.
 *
 * Khail - May 19/97
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "north";
}

public void
create_road()
{
    set_short("dirt road");
    set_long("   You are on a dirt road leading northwards " +
        "away from the piers into the center of Port Macdunn. " +
        "Stone buildings flank the road to the east and " +
        "west, the latter of which appears to be the smithy " +
        "of a bladesmith. To the north, the road meets up " +
        "with a much wider street running east and west. " +
        "To the south, this road ends in a four-way " +
        "intersection before continuing down onto the " +
        "piers. A small thistle plant grows beside the " +
        "doorway into the smithy.\n");

    add_item(({"thistle plant","plant","thistle","thistles"}),
        "The thistles are small, prickly plants with purplish " +
        "flowers growing on the top, quite common in these " +
        "parts.\n");
    add_item(({"smithy"}),
        "The low building appears to be the forge of a " +
        "bladesmith. It's made of the same stone blocks " +
        "as the other buildings in the village, but a " +
        "small crest above the door bears a sword and " +
        "anvil, the mark of the bladesmith crafthall.\n");
    add_item(({"crest","mark"}),
        "Engraved into a brass, tarnished plaque, is " +
        "a sword upon an anvil. This is the symbol of the " +
        "bladesmith's crafthall, and evidence that the " +
        "smith within has been trained by masters in the " +
        "craft of forging blades.\n");

    add_exit(ROOM + "road_9_7", "north");
    add_exit(ROOM + "road_9_9", "south");
    add_exit(ROOM + "bladesmith_forge", "west");
}
