/*
 * /d/Shire/eastroad/western/wdown_01.c
 *
 * A passage way off the well in the Shire
 * Finwe, Feb 2019
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include "local.h"

void reset_shire_room();

void
create_room()
{
    set_short("An underground tunnel");
    set_long("This is an underground tunnel. It is rough looking and " +
        "irregularly shaped. Roots hang from the ceiling and grow down " +
        "the walls. The ground is uneven and covered with rocks. The " +
        "tunnel runs northeast into the darkness and south to the bottom " +
        "of the well.\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();

    set_room_tell_time(60);
    add_room_tell("Water drips from the ceiling.");
    add_room_tell("Thundering sounds echo from above.");
    add_room_tell("Some pebbles fall from the ceiling.");

    add_item(({"rocks", "smooth rocks"}),
        "The rocks are dark and smooth from years of water rushing " +
        "over them. Now they are dry and half buried in the dirt.\n");
    add_item(({"ground"}),
        "The ground is covered with dirt, many rocks, and pebbles.\n");
    add_item(({"dirt"}),
        "The dirt is fine sand. It covers the ground and full of smooth " +
        "rocks.\n");
    add_item(({"roots"}),
        "The roots are large and long, while others are short and fine. " +
        "The long roots criss-cross down the walls and the short fine " +
        "roots hang from the ceiling.\n");
    add_item(({"large long roots", "large roots", "long roots",
            "large long root", "large root", "long root"}),
        "The roots are thick and dark colored, and grow in a cross-cross " +
        "pattern. They are many and fibrous, forming a mat along the " +
        "walls and across the ceiling.\n");
    add_item(({"short fine roots", "short roots", "fine roots",
            "short fine roots", "short roots", "fine roots"}),
        "The short fine roots are light colored and are thin, forming " +
        "a mat on the ceiling. Some of the roots hang down from " +
        "the ceiling.\n");
    add_item(({"walls"}),
        "The tunnel walls are rough looking, like they were carved by " +
        "water. Roots grown down through them. The walls are made of " +
        "soft dirt and rocks.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling is rough looking with roots hanging from it.\n");

    add_exit(EAST_R_DIR + "wdown", "south");
    add_exit(EAST_R_DIR + "wdown_02", "northeast");
}

void
reset_shire_room()
{
    ::reset_shire_room();
}

void
init()
{
    ::init();
}
