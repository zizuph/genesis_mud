/*
 * /d/Gondor/lebennin/road/fieldr7.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 *  3-Feb-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#define MAX_RAB 2

static object *Rabbit = allocate(MAX_RAB);

public void
create_area_room()
{
    set_area("southeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");
    add_exit(LEB_DIR + "road/fieldr6", "west", 0, 2);
    set_extraline("This is a beautiful flat field in Lebennin. You feel "+
        "you could stay here for a while.");

    set_up_herbs( ({ HERB_DIR + "foxglove", HERB_DIR + "curugwath",
		     HERB_DIR + "myrtle", }),
		 ({"bushes","bush","plain","ground","grass"}), 6);
    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Rabbit, NPC_DIR + "wrabbit", 120.0 + rnd() * 120.0, LEB_DIR);
    (Rabbit - ({ 0 }))->set_random_move(5 + random(11));
}
