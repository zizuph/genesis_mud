/*
 * 	c_trail.c			Styles.   3 Mar 1993
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

    set_short("Coast trail");
    set_long("You are on the edge of some misty moors, walking along a " +
        "coastal trail made from fieldstones. Small groves of trees rise up " +
        "through the blanket of brightly coloured wildflowers and tall green " +
        "grasses that cover the low hills of the moors. The misty fog is " +
        "rather thick around here, obscuring your view in almost all " +
        "directions save to the east where the blue waves of the Pen Sea " +
        "crash up against a long sandy beach. The path you are on " +
        "seems to sink into the moors here, providing passage only to " +
        "the south.\n");

    add_trees(0);

    add_exit("/d/Sparkle/guilds/new_merc/rooms/temporary_camp", "northwest",
        0, 1, 1);
    add_exit(THIS_DIR + "moor3","south");

    set_no_exit_msg(({"northeast","east"}),
        "You take a step into the rolling waves of the Pen Sea that " +
        "are crashing up against the shore. It seems obvious that you " +
        "cannot go any further in this direction.\n");
    set_no_exit_msg(({"southwest","west","north","southeast"}),
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
    add_item(({"path","stone path","small path","small stone path","trail"}),
        "This path has been made from hundreds of flat fieldstones which " +
        "have been laid atop the wet moorland. The path comes from the " +
        "south, but the stones seem to have sunken into the moors here. " +
        "At first you thought the trail had disappeared entirely, but " +
        "you notice that trail once continued more clearly to the " +
        "northwest.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}