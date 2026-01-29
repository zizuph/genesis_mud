#pragma strict_types

#include "defs.h"
inherit STDROOM;
inherit "/std/room";

string extra;

public void
create_crypt()
{
    set_short("in what appears to be a crypt");
    set_long("You are in what appears to be a crypt of some " +
        "sort. At first glance, it looks much like the catacomb " +
        "passages, with smoothly cut surfaces apparently " +
        "hewn into the surrounding stone. However, it is " +
        "conspicuously free of dust, and there are no sign of " +
        "the torch sconces which line the walls in the " +
        "catacombs. " +
        (stringp(extra) ? extra : "") + "\n\n");

    INSIDE;
    DARK;

    add_item(({"wall", "walls"}),
        "The walls are smoothly finished, and remarkably " +
        "free of any kind of aging whatsoever. If not for " +
        "the musty smell in the air, you'd swear this room " +
        "was still relatively new, but there's no mistaking " +
        "the smell of centuries gone by.\n");
    add_item(({"floor", "ground"}),
        "The floor of the crypt is immaculate, and unlike " +
        "the floors in the catacombs, is carefully tiled with " +
        "tightly interlocked flagstones.\n");
    add_item(({"flagstones"}),
        "The flagstones which tile the floor were placed " +
        "by a master. There are places where you can't even " +
        "see seams between some of them.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the crypt is quite ordinary. It's " +
        "solid and well finished, but unremarkable in any " +
        "real sense of the word.\n");
}
