#include "defs.h"

inherit GROTTOBASE;

public void
create_room()
{
    set_short("a narrow ledge at the end of a tunnel");
    set_long("You are on a narrow ledge, which stands " +
        "at the end of a darkened tunnel that leads " +
        "eastwards. You appear to be in a massive "+
        "cavern of some sort, as the ledge seems to " +
        "be the only thing jutting out from what is " +
        "otherwise a sheer rock wall. As far as the " +
        "light will permit, all you can see up, " +
        "down, or on either side is smooth stone merging " +
        "with distant shadows. The only visible, and " +
        "reasonably safe, means of passage from here " +
        "is through the tunnel, or out across a narrow " +
        "suspension bridge that leads westwards " +
        "into the darkness. The huge cavern echoes " +
        "with the sound of running water, and although " +
        "you cannot discern its origins, with the " +
        "echoes it seems to be coming from all " +
        "around you.\n\n");

    INSIDE;
    DARK;

    add_item(({"ledge"}),
        "The ledge upon which you stand is little more than a " +
        "narrow outcrop of stone from the otherwise sheer stone " +
        "wall from which the tunnel to the east emerges.\n");
    add_item(({"tunnel"}),
        "A dark tunnel vanishes into the sheer cavern wall here.\n");
    add_item(({"cavern"}),
        "You can't see much of it. In fact almost nothing except " +
        "the wall upon which you are standing now. The rest of " +
        "the cavern is cloaked in darkness.\n");
    add_item(({"wall"}),
        "The ledge you are upon appears to be located high upon " +
        "a steep wall of a cavern of some sort. It is completely " +
        "sheer, and the only way off of it, short of leaping to " +
        "your death, is across the bridge or through the tunnel.\n");
    add_item(({"bridge"}),
        "The narrow bridge looks to be a type of suspension bridge, " +
        "and not a very well constructed one, at that. It seems " +
        "to be made of little more than short boards lashed " +
        "across long, thick ropes.\n");
    add_item(({"boards","short boards"}),
        "The boards that comprise the floor of the bridge are " +
        "ancient, and now severely rotted.\n");
    add_item(({"rope", "ropes"}),
        "Attached to cavern wall here, thick ropes stretch out " +
        "the darkness, forming the spine of the suspension bridge. " +
        "while very strong, they have been subjected to years of " +
        "fraying and rot, and look as if they could snap any " +
        "moment.\n");

    add_exit(GROTTO + "tunnel_1", "east");
    add_exit(GROTTO + "e_bridge", "west");
}
