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

#define SOUTH    "m19"
#define EAST    "m15"
#define WEST    "m13"
#define SE        "m20"
#define SW        "m18"
#define NW        "m10"
#define NE        "m11"


object guard;

void
create_dunlending()
{
    set_short("A wide-open meadow in Anorien");
    set_long("You find yourself in an expansive meadow a ways away "
        + "from the trees in an old pine forest. "
        + "@@extra_line@@" + "Grass and wildflowers grow abundantly "
        + "here, supporting the many deer who live in the forest. "
        + "Many hours walk to the south, the White Mountains loom "
        + "large, their snow-capped peaks rising above the pine "
        + "trees.\n");
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
        enter_tent("m14t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);


}




