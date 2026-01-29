/*
 * 	moor3.c			Styles.   3 Mar 1993
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
    set_long("You are in the middle of some misty moorland, walking along a " +
        "winding path made from fieldstones. The low hills of the moors " +
        "boast small groves of trees, surrounded by blankets of vividly " +
        "coloured wildflowers and tall green grasses. The fog is thick " +
        "enough in most directions that you have difficulty seeing very " +
        "far, although a long sandy beach is visible to the southeast where " +
        "the Pen Sea crashes against the shore. Piercing the mists, the " +
        "stone path spreads out to permit passage in the four cardinal " +
        "directions: north, east, south and west.\n");

    add_trees(1);

    add_exit(THIS_DIR + "c_trail","north");
    add_exit(THIS_DIR + "moor2","west");
    add_exit(THIS_DIR + "n_shore","south");
    add_exit(THIS_DIR + "moor4","east");
    add_exit(THIS_DIR + "stockade","southwest",0,1,1);

    set_no_exit_msg(({"southeast"}),
        "You take a step into the rolling waves of the Pen Sea that " +
        "are crashing up against the shore. It seems obvious that you " +
        "cannot go any further in this direction.\n");
    set_no_exit_msg(({"northeast","northwest"}),
        "You attempt to leave the stone path to make your own way across " +
        "the moors, but you find that the land here is too wet here. You " +
        "will have to try to find an alternative route.\n");

    add_item(({"beach","sandy beach","sand"}),
        "A long sandy beach has been created where the Pen Sea brushes " +
        "up against the moors to the southeast. The beach seems to " +
        "continue to both the south and east from here.\n");
    add_item(({"sea","coast","shore","pen sea","water","waters"}),
        "You can see the choppy waves of the Pen Sea rolling up a sandy " +
        "beach to the southeast.");

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}