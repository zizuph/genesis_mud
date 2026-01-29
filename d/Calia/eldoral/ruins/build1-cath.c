#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("southern chapel entrance");
    set_long("You are in a wide corridor, the ceiling of which " +
        "stretches far beyond your line of sight into shadowy " +
        "recesses amidst the rafters. Along the walls hang the " +
        "tattered remains of once-glorious tapestries, and the " +
        "toppled heaps of a number of decrepit statues and urns. " +
        "The corridor leads into darkness to the west, and further " +
        "eastward through a set of massive broken doors.\n\n");

    add_item(({"walls", "north wall", "south wall"}),
        "The walls themselves are heavily aged, the southern " +
        "wall showing the most signs of fatigue, with gaping holes " +
        "slashed across the surface in a number of places in the " +
        "higher points of the wall, allowing beams of light to " +
        "shine through, which reflect off the ancient dust in the " +
        "air like some spirit of the light, frozen in place.\n");
    add_item(({"doors", "massive doors", "broken doors"}),
        "The doors themselves must have once been magnificently " +
        "carved, bearing the cracked and faded marks resembling " +
        "people upon the wooden surfaces, but time, water, and " +
        "insects have destroyed much of what once was, and they " +
        "now hang ajar, their hinges siezed.\n\n");
    add_item(({"ceiling", "roof"}),
        "The roof is high and dark enough that the ceiling is " +
        "beyond the range of your vision.\n");
    add_item(({"floor", "ground", "dust", "debris"}),
        "The large collection of dust and debris around the " +
        "base of the doors shows evidence of the amount of " +
        "time that has passed since this structure has seen " +
        "use.\n");

    INSIDE;

    add_exit(RUIN + "build1", "west");
    add_exit(RUIN + "cath-build1", "east", "@@east_msg");
}
