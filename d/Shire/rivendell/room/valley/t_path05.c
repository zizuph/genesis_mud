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
    set_extraline("The stone path follows the shoreline here " +
        "as it wanders alongside the river. The air is filled " +
        "with the sounds of the water and the smells of the " +
        "fruit trees. The ground slopes towards the river.");

    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made out of flat stones that closely fit " +
        "together.\n");
    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams  for a criss-cross and diamond " +
        "patterns across the face of the house. Gables extend from " +
        "the roof. The roof is covered with cedar shingles.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("garden",
        "The garden surrounds the house. Many fruit trees, " +
        "vegetables, and edible plants can be seen growing " +
        "there. A split-rail fence surrounds the garden.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes west over " +
        "polished rocks. The water is clear. Its gentle music " +
        "fills the air.\n");

    set_fence("They are secured to posts that have " +
        "been sunk into the ground.\n");

    set_drink_from(({"river", "river bruinen", "bruinen"}));

    add_path_herbs();

    add_exit(VALLEY_DIR + "t_path06",  "east");
    add_exit(VALLEY_DIR + "t_path04",  "west");
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
