/*
 *	/d/Gondor/lebennin/road/fieldr2.c
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_RAB 4

public void    reset_room();

static object *Rabbit = allocate(MAX_RAB);

public void
create_area_room()
{
    set_area("northeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");
    add_exit(LEB_DIR + "road/fieldr3", "northeast", 0, 2);
    add_exit(LEB_DIR + "road/fieldr1", "west",      0, 2);
   
    add_item(({"pond","water"}), BSN(
       "The pond to your east seems to have something crawling across its "+
       "surface."));
   
    set_extraline("You are in a nice, tranquil field and all around you, nature sings."+
        " There is a pond to your east, but here you might see a rabbit or two.");
    
    set_up_herbs( ({ HERB_DIR + "basil", HERB_DIR + "savory",
                      HERB_DIR + "ungolestel", }),
		 ({"pond","ground","grass","bush","bushes"}), 8);
    set_drink_from("pond");
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    BEACH;

    reset_room();
   
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Rabbit, NPC_DIR + "wrabbit", 120.0 * 120.0 * rnd(), LEB_DIR);
    (Rabbit - ({ 0 }))->set_random_move(5);
}

public void
init()
{
    ::init();
    init_drink();
}

