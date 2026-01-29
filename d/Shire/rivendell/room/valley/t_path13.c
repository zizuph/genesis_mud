/*
 * The terrace path along the river in Imladris
 * By Finwe, December 1997
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit VALLEY_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";

void
create_valley_room()
{
    set_extraline("You steadily climb upwards as you walk " +
        "along the path. It wanders amoung the trees that grow " +
        "on either side of it. Some grow alongside the river " +
        "and shade it from your view. The land dips slightly " +
        "towards the river.");

    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made out of flat stones that closely fit " +
        "together.\n");
    add_item(({"last homely house", "house"}),
        "The house is hidden by the trees.\n");
    add_item("roof",
        "The roof is hidden by the trees.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes west over " +
        "polished rocks. The water is clear. Its gentle music " +
        "fills the air.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes west over " +
        "polished rocks. The water is clear. Its gentle music " +
        "fills the air.\n");

    set_drink_from(({"river", "river bruinen", "bruinen"}));

    add_path_herbs();

    add_exit(VALLEY_DIR + "t_path14",  "northeast");
    add_exit(VALLEY_DIR + "t_path12",  "southwest");

    reset_room();
}

void
reset_room()
{
    set_searched(0);
}

void
init()
{
    ::init();
    init_drink();
}

string short_desc()
{
    return ("The terrace path along the Bruinen");
}
