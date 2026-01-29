#include "defs.h"

inherit GROTTOBASE;

public void
create_room()
{
    set_short("on a narrow bridge in a dark cavern");
    set_long("You are on a very narrow suspension " +
        "bridge, but what it crosses you can't be " +
        "sure, as everything around you is engulfed " +
        "in shadows. If there is anything to see here " +
        "besides the bridge itself, it lies far beyond " +
        "the limits of the available light. The bridge " +
        "itself only serves to heighten your " +
        "apprehension of what lies beneath, as it " +
        "doesn't appear to be very solidly constructed, " +
        "little more than a series of short boards " +
        "tied across two long ropes leading east " +
        "and west. Your only clue as to what lies " +
        "beneath is the ever-present echoing of " +
        "running water somewhere in this massive " +
        "cavern beneath the castle.\n\n");

    INSIDE;
    DARK;

    add_item(({"shadows"}),
        "Everything around is is cloaked in shadows, you can " +
        "see nothing except the bridge you walk on, no walls, " +
        "no ceiling, no ground. Everything is darkness.\n");
    add_item(({"bridge"}),
        "The narrow bridge appears to be ancient and quite " +
        "fragile in design. It's little more than a couple " +
        "thick ropes across which have been lashed several " +
        "short boards to walk on.\n");
    add_item(({"ropes", "rope", "thick ropes"}),
        "Frayed and partially rotted, the ropes look like they " +
        "could give way any second.\n");
    add_item(({"boards"}),
        "The boards are old and terribly rotted out, and look " +
        "like it wouldn't take much weight for them to break.\n");

    add_exit(GROTTO + "ledge", "east");
    add_exit(GROTTO + "pillar", "west");
}
