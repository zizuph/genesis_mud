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

#define NORTH    "f3"
#define SOUTH    "f8"
#define WEST    "f5"
#define SE        "f9"
#define SW        "f7"
#define NW        "f2"

object guard;

void add_buck();
void
create_dunlending()
{
    set_short("In a forest in Anorien");
    set_long("Deep into the forest, all you see are pine trees in every "
        + "direction. Undergrowth prevents you from moving eastward, but "
        + "everywhere else you would walk from between trees to between "
        + "trees, all the while crushing pine needles underfoot.\n");

    add_item( ({"underbrush", "brush"}), "The brush looks a lot like poison "
        + "oak! It's very thick and overgrown here, so you think it'd be "
        + "best not to walk through it.\n");

    add_item( ({"bird", "birds"}), "You cannot see the birds.\n");
    add_room_tell("Birds chirp from high up in the branches.");
    add_room_tell("You hear the 'cakaw, cakaw' of a raven from nearby.");
    add_room_tell("A bird flies between two trees.");


    set_no_exit_msg( ({"northeast", "east"}),
        "Thick underbrush prevents you from walking that direction.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast");


    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
        forest_climb("f6_up");
    }

    add_guard_down();
    add_buck();
}

void
reset_room()
{
    set_searched(0);
}

void
add_buck()
{
    add_npc("/d/Gondor/common/npc/buck");
       return ;
}