#include "defs.h"

inherit GROTTOBASE;

public void
create_room()
{
    set_short("atop a pillar in a dark cavern");
    set_long("You appear to be on a very small space atop " +
        "a tall pillar of some sort. It's rather difficult " +
        "to tell, since you can't see anything above, below " +
        "or to your sides, other than the small circle of stone " +
        "upon which you're standing. Everything else is " +
        "cloaked in darkness and shadows, although you do " +
        "detect the echoes of trickling and dripping water. " +
        "Everything, that is, except for two very old suspension " +
        "bridges, on sloping downwards to the north, and another " +
        "that goes straight across to the east.\n\n");

    INSIDE;
    DARK;

    add_item(({"floor","ground","space","pillar","top of pillar"}),
        "You are on what would seem to be a very tall pillar of " +
        "some sort. The pillar's surface is very uneven, however, " +
        "and the top seems to slant a little bit towards the north.\n");
    add_item(({"bridge", "bridges"}),
        "Two identical bridges lead from here in different " + 
        "directions. One leads off eastwards, and the other one " +
        "slopes downwards to the north.\n");
    add_item(({"north bridge"}),
        "The bridge to the north looks to slope downwards.\n");
    add_item(({"east bridge"}),
        "The bridge to the east appears to lead more or less " +
        "straight across, sloping neither up nor down.\n");

    add_exit(GROTTO + "n_bridge", "north");
    add_exit(GROTTO + "e_bridge", "east");
}
