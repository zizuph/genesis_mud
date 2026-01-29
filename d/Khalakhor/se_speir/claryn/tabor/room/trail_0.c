/*
 * /d/Khalakhor/se_speir/claryn/tabor/room/trail_0.c
 *
 * Danuine's Rest
 * This is the place of repose of Danuine the Woad Woman
 * in Khalakhor, on the hill overlooking Tabor Sogh.
 *
 * Vitwitch 09/2020
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include "room.h"

#define PLAINS "/d/Khalakhor/se_speir/plains/room/"
#define PENDRAGON_PATH "/d/Khalakhor/se_speir/claryn/tabor/pendragon/"
#define DANUINE "pendragon_woman"

inherit TRAILBASE;

object danuine;

void
reset_khalakhor_room()
{
    if(!objectp(danuine))
    {
        setuid();
        seteuid(getuid());
        danuine = clone_object(PENDRAGON_PATH + DANUINE);
        danuine->move(this_object());
    }
}

public void
create_khalakhor_room()
{
    create_trail();

    set_long("From the high crest of a grassy hill, amidst rocky "+
        "outcrops you see the sleepy little village of Tabor Sogh "+
        "far below, sitting at the edge of the sea to the south. "+
        "A lightly trampled grassy trail runs along the base of "+
        "the hill, leading into the village. To the west, the hill "+
        "drops sharply down to the sea and a harsh rocky shore.\n");

    reset_khalakhor_room();

    add_exit(ROOM + "trail_1", "down");
}
