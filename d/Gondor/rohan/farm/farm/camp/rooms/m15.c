/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

#define TENT    "_a_tent_sits_here"

#define SOUTH    "m20"
#define EAST    "m16"
#define WEST    "m14"
#define SE        "m21"
#define SW        "m19"
#define NW        "m11"
#define NE        "m12"


object guard;

void
create_dunlending()
{
    set_short("A meadow in Anorien");
    set_long("Everywhere you look, you see a sea of grass. The meadow "
        + "extends in every direction. "
        + "@@extra_line@@" + "You see campfire smoke rising at various "
        + "places throughout the meadow, indicating that many people "
        + "live here in addition to the animals. In the distance, you "
        + "can see the White Mountains.\n");
    add_meadow_forest("far to the east");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains look rugged and steep. They seem close, but "
        + "that's jus an illusion because of their size. In reality it would "
        + "take a day or two to walk to them--a day or two without any "
        + "trouble from Dunlendings or orcs.\n");
    add_item("underbrush", "Thick gnarled plants, many of them with "
        + "thorns, entertwine, making passage through the undergrowth "
        + "impossible.\n");
    set_no_exit_msg( ({"north"}),
        "You try to walk north but lose your footing.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow();
    meadow_herbs_1();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m15t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
