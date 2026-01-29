/*
 * monk_herbg_se.c
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
    set_long("A herb garden. " +
             "The woodsy perfume of fresh blooms fills the air " +
             "of this quaint little garden. Its lush herbs and " +
             "flowers appear to be in full bloom. In the middle of " +
             "the garden there is a well. The garden continues to " +
             "the west, and is bordered by thick bushes, but it " +
             "seems to be possible to get out to the east.\n");

    add_exit("p6", "east");
    add_exit("monk_herbg_sw", "west");
    add_exit("monk_herbg_ne", "north");
    add_exit("monk_herbg_well", "northwest");

    add_item("bushes", "The bushes seem thin enough to " +
             "to walk through to the east.\n");
}
