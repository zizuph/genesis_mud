#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("inside the southern archway of " + CASTLE_NAME);
    set_long("About you rises the heavy stone-lined walls of the southern " +
        "archway into " + CASTLE_NAME + ". It gives you the feeling of " +
        "being inside some deep cave, despite the fact it's only a few " +
        "paces deep. The stones within the walls show brutal evidence " +
        "of the years which they have seen, with a number of cracks and " +
        "gaps where the bits of stone have given up their grasp on the " +
        "others and fallen to the ground. To the south, you can see the " +
        "thick needles and dark trunks of the surrounding evergreen " +
        "forest, and to the north lies the southern courtyard of the " +
        "ruins.\n\n");

    add_item(({"walls", "ceiling", "roof"}),
        "To either side of you, rough stone walls rise up to " +
        "to top of the archway, coming together to form the " +
        "ceiling.\n");
    add_item(({"ground", "floor"}),
        "The ground here is strewn with pieces of stone which " +
        "have fallen from the walls and ceiling, obscuring " +
        "whatever might lie beneath.\n");
    add_item(({"pieces of stone"}),
        "The ground here is covered with small pieces of grey " +
        "stone that have fallen from the walls and ceiling of " +
        "the archway.\n");
    add_item(({"forest", "trees"}),
        "The the south, the massive evergreen forest obscures " +
        "completely dominates your view. Rising so high their " +
        "top-most branches are obscured in mist, their age is " +
        "indeterminable.\n");
    add_item(({"courtyard"}),
        "To the north, a wide courtyard spreads out before you.\n");
    add_item(({"sky", "mist"}),
        "The sky here is completely obscured by the thick white " +
        "mist that seems to hang perpetually above the island.\n");

    add_exit(RUIN + "sw_court_sw", "north");
    add_exit(RUIN + "south_entry", "south");
}
