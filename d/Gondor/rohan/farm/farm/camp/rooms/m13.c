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

#define SOUTH    "m18"
#define EAST    "m14"
#define SE        "m19"
#define SW        "m17"
#define NE        "m10"


object guard;

void
create_dunlending()
{
    set_short("A wide-open meadow");
    set_long("In the distance, you see pine trees--even from here you "
        + "can tell they're very, very large--and beyond them, the peaks "
        + "of the White Mountains. But here and for as far as you "
        + "could shoot an arrow, it's nothing but wide-open meadow. "
        + "Grass grows tall and thick, almost up to your knees, and "
        + "skunk cabbage is everywhere. "
        + "@@extra_line@@" + "\n");

    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains look rugged and steep. They seem close, but "
        + "that's jus an illusion because of their size. In reality it would "
        + "take a day or two to walk to them--a day or two without any "
        + "trouble from Dunlendings or orcs.\n");
    add_item("underbrush", "Thick gnarled plants, many of them with "
        + "thorns, entertwine, making passage through the undergrowth "
        + "impossible.\n");
    set_no_exit_msg( ({"north", "west", "northwest"}),
        "The underbrush prevents you from going that way.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");

    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m13t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);


}




