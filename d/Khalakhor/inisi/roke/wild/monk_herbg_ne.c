/*
 * monk_herbg_ne.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "wild/monk_herbg_base";

object places;

void
create_herbg_room()
{
    set_long("The song of some little birds " +
             "can be heard in the distance. The garden is bordered " +
             "by thick bushes to the east and north and continues " +
             "to the south and west. There is a small rock here.\n");

    add_exit("monk_herbg_se", "south");
    add_exit("monk_herbg_nw", "west");
    add_exit("monk_herbg_well", "southwest");
    add_item("rock", "It's just a rock.\n");
}
