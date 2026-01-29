/*
 * monk_herbg_nw.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "wild/monk_herbg_base";

void
create_herbg_room()
{
    set_long("There is a tall oak growing here, " +
             "shrouded in ferns, and at its base is a small bench. " +
             "To the west and north thick bushes border the garden. " +
             "The garden continues to the south and east.\n");

    add_exit("monk_herbg_ne", "east");
    add_exit("monk_herbg_sw", "south");
    add_exit("monk_herbg_well", "southeast");
    add_item("bench", "This is a little stone bench. Perhaps in " +
             "time you will be able to sit on it.\n");
    add_item((({"tree", "oak"})),
             "This is a very unique tree. Its gnarled " +
             "branches twist and turn in a breathtaking " +
             "pattern, causing your eyes to linger for a " +
             "moment ...\n");
    add_item("ferns", "The lush green ferns are feathery and soft.\n");
}
