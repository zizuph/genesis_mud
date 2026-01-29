#include "plains.h"

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("on a stone bridge crossing the Sora");
    set_long("   You are on an old stone bridge spanning " +
        "the river Sora. The Sora empties further " +
        "south into the harbour Cala Fasgadh. Grassy " +
        "hills spread out on both sides of the " +
        "river, the cold clear water of the Sora " +
        "snaking between the hills like a gossamer " +
        "ribbon, to it's origins in the Highland " +
        "mountains which you can see as a dark " +
        "purplish mass rising into the sky far " +
        "to the north.\n");

    add_item(({"sky","clouds"}),
        "High above you, thick clouds drift by in an " +
        "otherwise clear blue cky.\n");
    add_item(({"bridge"}),
        "The bridge beneath you is ancient, made of " +
        "carefully placed granite blocks. The " +
        "construction is simple, but sturdy.\n");
    add_item(({"sora","river","Sora","water"}),
        "The waters of the Sora are cold and clear, " +
        "fed from the lochs in the Highlands far to " +
        "the north.\n");
    add_item(({"hills","hill"}),
        "Low rolling hills cover the plains as far " +
        "as the eye can seen.\n");
    add_item(({"mountains", "highlands"}),
        "In the far north, you can dimly distinguish the " +
        "faded, purple-blue tinge of the mountains of the " +
        "Highland region.\n");

    add_exit(PLAINS + "plains_25_10", "east");
    add_exit(PLAINS + "plains_23_10", "west");
}
