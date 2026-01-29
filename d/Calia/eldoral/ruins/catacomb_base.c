#pragma strict_types

#include "defs.h"

inherit STDROOM;

string extra;

public void
create_catacomb()
{
    set_short("in the catacombs beneath " + CASTLE_NAME);
    set_long("You are in some catacombs beneath " +
        CASTLE_NAME + ". The wide, square-cut passage is hewn through " +
        "the natural rock upon which the castle itself was built on " +
        "and around. The surfaces are all smoothly cut, but the ravages " +
        "of time have left a thick film of dust on them, yet surprisingly " +
        "free of cobwebs, moss, or other growth. Embedded within the walls " +
        "are a pair of rust-coated iron sconces, once holding torches but " +
        "now holding little more than the dust of many years. " +
        (stringp(extra) ? extra : "") + "\n\n");

    add_item(({"floor", "ground"}),
        "The floor of the passage is largely the same as " +
        "the other surfaces, apparently cut right down " +
        "into the rock of the island, it's not tiled " +
        "or flagstoned in any way. The floor is covered " +
        "in a thick veil of dust and silt that has " +
        "collected over the years, but is otherwise " +
        "featureless.\n");
    add_item(({"dust", "silt", "veil"}),
        "The ground here is covered in a thick veil of " +
        "dust and silt, the cast-off skin of many years.\n");
    add_item(({"walls", "wall"}),
        "The walls of the passage appear to be cut from " +
        "solid stone, making this more of a tunnel than " +
        "a structure of any kind. They are well " +
        "crafted, however, as they are very well planed " +
        "and smoothed, with edges as crisp as any " +
        "mason could achieve. Time has taken its toll on "+
        "them, however, and they're now stained with water " +
        "seepage, and dark reddish-brown streaks running " +
        "from the bases of the rusted out sconces down " +
        "to the floor.\n");
    add_item(({"sconces", "iron sconces"}),
        "These iron racks are firmly embedded in the wall, and " +
        "scorch marks on the stone behind them serve as " +
        "evidence they once held torches, a long, long " +
        "time ago.\n");
    add_item(({"streaks"}),
        "Running from the bases of the sconces all the " +
        "way down to the floor, large rust stains add a " +
        "touch of unwanted colour to the old walls.\n");
    add_item(({"stains", "discolourations"}),
        "The walls are covered in discolourations where " +
        "water has seeped in somewhere and dried on the walls.\n");
    add_item(({"ceiling", "roof"}),
        "The ceiling of the passage is as unattractive " +
        "as the other surfaces. Simply cut straight out of " +
        "the stone here, it's largely featureless.\n");
    INSIDE;
    DARK;
    add_prop(ROOM_I_NO_CLEANUP, 1);

}
