/*
 * information.c
 *
 * This is a module which contains information on the
 * location of various places of interest in the village
 * of Tabor Sogh, like shops or the town hall.
 *
 *
 * Khail - August 1, 1997
 */
#pragma strict_types
#pragma no_clone

#include "/d/Khalakhor/sys/paths.h"
#include "village.h"

inherit INFO_BASE;

public void
create_info()
{
    options = ([]);

    aliases = ([
        "shop": ({"shop", "store", "delivery office", "delivery"}),
        "pub": ({"pub","tavern","inn","bar"}),
        ]);

    coords = ([
        "shop": ({2,5}),
        "pub": ({2,8}),
        "kirk": ({2,3}),
        ]);

    area_name = "Tabor Sogh";
    global_coords = VILLAGE_COORDS;
}
