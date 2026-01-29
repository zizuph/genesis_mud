/*
 * Garden room of the Noldor Guild
 * By Finwe, January 2020
 */

#pragma strict_types

#include "noldor.h"
#include "/d/Shire/rivendell/local.h"

inherit BUILDING_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";

void
create_guild_room()
{
    set_short("An enclosed garden room");
    set_long("This is a garden room with walls made of glass. The sound " +
        "of water echoes from a small fountain set in the center of " +
        "the garden. A stone path wanders past lush plants. " +
        "Lamps and @@daylight_desc@@, flowing in from the walls, " +
        "fills the room with light. \n");

    remove_item("arch");
    remove_item("arches");
    remove_item("carved trees");
    remove_item("ceiling");
    remove_item("chair");
    remove_item("chairs");
    remove_item("divan");
    remove_item("doorways");
    remove_item("floor");
    remove_item("gateway");
    remove_item("grass");
    remove_item("lawn");
    remove_item("settee");
    remove_item("trees");
    remove_item("wiildflowers");

    add_item(({"walls", "glass walls", "windows", "ceiling"}),
        "The walls and ceiling are made of large panes of glass, which " +
        "are floor to ceiling and filled with @@daylight_desc@@.\n");
    add_item(({"path"}),
        "The path is made of white, crushed rocks. It runs through the " +
        "garden and past lush plants.\n");
    add_item(({"white rocks", "white crushed rocks", "rocks", "crushed rocks"}),
        "XXX \n");
    add_item(({"fountain"}),
        "XXX \n");
    add_item(({"plants", "lush plants"}),
        "XXX \n");
    add_item(({"glass", "planes of glass"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    



    set_drink_from(({"fountain"}));

    reset_room();

    add_exit(NOLGLD_DIR + "board_rm", "south");
    add_exit(NOLGLD_DIR + "garden2", "west");
    add_exit(NOLGLD_DIR + "rack_rm", "east");

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
