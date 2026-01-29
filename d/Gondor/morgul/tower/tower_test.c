/*
 * /d/Gondor/morgul/tower/tower_0c.c
 * The central room on the ground floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 * Morbeche, 20 Feb 2000 -  Changed to make it so someone cannot
 *                          enter the throne room without agreeing
 *                          that the Nazgul may kill them at will
 *                          and instantly (so I can put in some
 *                          torture devices in the room that do 
 *                          damage and may kill them) 
 */
inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"



void create_morgul_tower_room()
{
    remove_prop(ROOM_M_NO_TELEPORT);

    set_level(0);
    set_room_type("large testing hall");
    set_extra_long("This is a room strictly for testing purposes. The two rows of pillars extend to the northeast and " +
        "southwest as far as you can see. Running around one of the pillars " +
        "of the northwestern row, a spiral staircase is climbing up to the " +
        "next level of the tower.");


}

