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

#define SOUTH    "m11"
#define EAST    "f13"
#define WEST    "m8"
#define SE        "m12"
#define SW        "m10"
#define NW        "m6"
#define NE        "m7"


object guard;

void
create_dunlending()
{
    set_short("In a meadow in Anorien");
    set_long("Signs of human habitation are all around you. Campfires "
        + "send smoke up from distant parts of the meadow. Grass looks "
        + "trampled and retrampled, as if people have been through here "
        + "often. "
        + "@@extra_line@@" + "To the south you notice the White Mountains, "
        + "home to snow-capped peaks and, rumor has it, trolls.\n");
    add_item( ({"grass", "ground"}), "The grass looks as if it's been walked "
        + "over time and time again, probably in heavy military style "
        + "boots, and not a woodsman's moccasin.\n");
    add_item( ({"herb", "herbs"}), "You see many different kinds of herbs "
        + "here, but it's hard to identify them without taking a closer "
        + "look.\n");
    add_item( ({"branch", "branches"}), "The branches are very high up in "
        + "the trees. This is truly an ancient forest to have such tall "
        + "straight trees.\n");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
        "The White Mountains look tall and imposing from here. Rumor has it "
        + "that trolls live in the deep crevices and caves of those "
        + "mountains.\n");

    set_no_exit_msg( ({"north"}), "You "
        + "cannot find a trail leading in that direction.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SW, "southwest",0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_room_tell("You hear something snarling in the grass.");
    add_meadow_forest("east");



    add_meadow();
    meadow_herbs_3();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m9t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
