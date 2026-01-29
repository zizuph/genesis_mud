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
    set_extraline("The path leads northeast towards the " +
        "mountains. A grove of trees grows alongside the " +
        "western edge of the path, providing cool shade and " +
        "comfort. The river flows south and west past you.");

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

    set_drink_from(({"river", "river bruinen", "bruinen"}));

    add_path_herbs();

    add_exit(VALLEY_DIR + "v_path11",  "west");
    add_exit(VALLEY_DIR + "t_path13",  "northeast");

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
