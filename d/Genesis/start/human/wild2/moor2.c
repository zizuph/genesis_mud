/*
 * 	moor2.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

void
create_wild_room()
{
    set_items_sparkle();
    set_items_moor();
    set_herbs();

    set_short("Misty moor");
    set_long("You are wandering across some misty moorland, following a " +
        "narrow path made from fieldstones. Several gentle hills, covered " +
        "with bright wildflowers that hide behind the long grasses, rise " +
        "up out of the wetland mists in every direction broken up only with " +
        "the occasional grove of rowan or yew trees. The fog is thick " +
        "enough in most directions that you have difficulty seeing very " +
        "far. You begin to suspect that the stone path, which branches off " +
        "to the east, south and west, was laid for two reasons. First, to " +
        "keep travellers out of the muddy wetlands and second, to " +
        "prevent them from becoming hopelessly lost!\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor1","west");
    add_exit(THIS_DIR + "stockade","south");
    add_exit(THIS_DIR + "moor3","east");
    add_exit(THIS_DIR + "n_shore","southeast",0,1,1);
    add_exit(THIS_DIR + "stream3","southwest",0,1,1);

    set_no_exit_msg(({"northwest","north","northeast"}),
        "You attempt to leave the stone path to make your own way across " +
        "the moors, but you find that the land here is too wet here. You " +
        "will have to try to find an alternative route.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}