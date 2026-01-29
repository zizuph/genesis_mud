/*
 * monk_herbg_sw.c
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
    set_long("The fresh sweet fragrance of " +
             "blossoms fills the air. To your west thick bushes " +
             "border the garden, making it impossible to go in " +
             "that direction. The garden continues to the north and " +
             "east. To the northeast you see a well.\n");

    add_exit("monk_herbg_se", "east");
    add_exit("monk_herbg_nw", "north");
    add_exit("monk_herbg_well", "northeast");
}
