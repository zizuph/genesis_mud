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

#define NORTH    "f2"
#define SOUTH    "f7"
#define EAST    "f6"
#define WEST    "f4"
#define SE        "f8"
#define SW        "m2"
#define NE        "f3"


object guard;

void
create_dunlending()
{
    set_short("In a forest, near a meadow in Anorien");
    set_long("Looking around, you see straight tall pine trees. "
        + "They stretch up toward the sky and are so tall that you "
        + "can't see the tops of them. You hear birds from the "
        + "high branches, but you cannot see them. Looking at the "
        + "ground, you see signs of recent human traffic.\n");

    add_item("ground", "You see broken twigs on the ground, interspersed "
        + "with bootprints.\n");
    add_item(({"bootprint", "boot print", "bootprints", "boot prints"}),
        "The bootprints look large and heavy. Likely they were made by "
        + "some type of military boot, not a woodsman's moccasin.\n");
    add_item( ({"underbrush", "brush"}), "The brush looks a lot like poison "
        + "oak! It's very thick and overgrown here, so you think it'd be "
        + "best not to walk through it.\n");
    add_item( ({"bird", "birds"}), "You cannot see the birds.\n");
    
    add_room_tell("Birds chirp from high up in the branches.");
    add_room_tell("You hear the 'cakaw, cakaw' of a raven from nearby.");
    add_room_tell("A bird flies between two trees.");
    
    add_forest_meadow("southwest");
    set_no_exit_msg( ({"northwest"}),
        "Thick underbrush prevents you from walking that direction.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0,0,1);
    
    add_forest();
    forest_herbs_3();
    if(!random(3))
    {
    forest_climb("f5_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}

