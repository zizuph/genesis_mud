#include "defs.h"

inherit GROTTOBASE;

public void
create_room()
{
    set_short("a narrow suspension bridge");
    set_long("You are on a very narrow, very old, suspension " +
        "bridge of sorts. Its construction is rather odd, " +
        "as it descends rather steeply downwards towards the " +
        "north. You can't see a whole lot of detail from here, " +
        "but looking down you think you can see reflections " +
        "off the surface of a body of water. That combined " +
        "the the everpresent trickling and dripping sounds " +
        "which echo around you in the shadows lead you to " +
        "the conclusion you're over a subterranean lake or " +
        "river.\n\n");

    INSIDE;
    DARK;

    add_item(({"reflection", "reflections"}),
        "It's hard to be sure, all you can really make out, is " +
        "the reflection might be yours, It's just a blur of " +
        "light, but it appears to move with you.\n");
    add_item(({"water", "lake"}),
        "You can't really see it, just hear it.\n");
    add_item(({"bridge", "narrow bridge", "suspension bridge"}),
        "The bridge you're on is a narrow suspension bridge, " +
        "which appears to have been made from long lengths of " +
        "thick rope, across which have been lashed narrow short " +
        "lengths of planks.\n");
    add_item(({"rope", "thick rope"}),
        "Rope appears to form the backbone of this bridge, it's " +
        "used for handrails, and for main supports on the edges " +
        "of the planks. It has definately seen better days, " +
        "however, as it is fraying and rotting out in a number " +
        "of places.\n");
    add_item(({"plank", "board", "planks"}),
        "The boards that form the actual 'floor' of the bridge " +
        "are nothing more than short lengths of planking that " +
        "have been lashed across the bottom suspension ropes.\n");

    add_exit(GROTTO + "s_grotto", "north");
    add_exit(GROTTO + "pillar", "south");
}
