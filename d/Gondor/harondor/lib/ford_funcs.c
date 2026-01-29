/*
 *  /w/serif/harondor/lib/ford_funcs.c
 *
 *  Functions that contain base-room repeats for ford rooms in Harondor.
 *
 *  Serif 30 June 2001
 *  Tells inspired by Alto.
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

void
add_ford_items()
{
    add_item(({"ford", "fords", "river", "poros", "river poros"}),
        "The River Poros widens here, becoming shallow enough to cross "
        + "safely during most of the year. The ford continues to the "
        + "north and the south.\n");
    add_item(({"rock", "rocks", "riverbed", "slippery rock", 
        "slippery rocks"}), "The riverbed here is lined with slippery "
        + "rocks which shift underfoot and in the current, making "
        + "passage treacherous.\n");
    add_item(({"channel", "river channel"}), "The river channel widens "
        + "out here and the water is often shallow enough to cross. "
        + "The current is still strong though, and pushes against you "
        + "firmly.\n");
    add_item(({"current"}), "The current pushes at you relentlessly "
        + "as you stand in the middle of the river.\n");
    add_item(({"shore", "shores"}), "There are shores on the north and "
        + "south of the ford.\n");
    add_item(({"north shore", "north shores", "ithilien"}), "The land "
        + "of Ithilien lies to the north of the river, beginning at "
        + "the north shore of the ford.\n");
    add_item(({"south shore", "south shores", "southern shore", 
        "harondor"}), "The land of Harondor lies to the south of the "
        + "river, beginning at the south shore of the ford.\n");
    add_item(({"road", "harad road"}), "Across the river to the north, "
        + "the Harad Road continues through Ithilien. To the south, "
        + "the road crosses Harondor on its way toward Harad.\n");
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks"}), "The peaks of the Ephel Duath loom ominously "
        + "in the east.\n");
    add_item(({"plant", "plants", "bush", "bushes", "dense bushes", 
        "thicket", "thickets", "thorn", "thorns", "vegetation"}), "On "
        + "the shores, dense thickets of bushes and other plants crowd "
        + "along the river.\n");
    add_item(({"ripple", "ripples", "surface"}), "The surface of the "
        + "river constantly ripples and moves.\n");
    add_item(({"surroundings"}), "You are standing in the middle of "
        + "a ford in a wide, shallow river. The water courses around "
        + "you.\n");
    add_item(({"fly", "flies", "biting fly", "biting flies", "black fly",
        "black flies", "black biting fly", "black biting flies"}), "A few "
        + "black flies buzz through the humid air.\n");
    add_item(({"insect", "insects"}), "A few insects fly through the "
        + "air and over the water around you.\n");
    add_item(({"sky", "skies"}), "The sky is high above you.\n");

} 

/* These tells are common to the south road rooms of Harondor. */

void
add_ford_tells()
{
    add_tell("The river rushes around you.\n");
    add_tell("Something heavy splashes in the river.\n");
    add_tell("Something small splashes in the river.\n");
    add_tell("You feel more tired as the river pushes against you.\n");
    add_tell("The surface of the river ripples.\n");
    add_tell("You almost lose your footing as you stumble over a rock.\n");
    add_tell("Something quickly floats by but is gone before you can "
        + "examine it closer.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("A large black fly whizzes past your head.\n");
}
