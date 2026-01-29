/*
 * /d/Gondor/lebennin/road/fieldr3.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_MIDGE 5

static object *Midge = allocate(MAX_MIDGE + random(MAX_MIDGE));

public void
create_area_room()
{
    set_area("northeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");
   
    add_exit(LEB_DIR + "road/fieldr2", "southwest", 0, 2);
   
    add_item(({"trees","tree"}), 
         "The trees around here are not so tall as the mound far to your south.\n");
    add_item(({"path","trail"}), 
         "The narrow path which you followed in ends here.\n");
    add_item(({"pond","water"}), BSN(
         "The pond to your south seems to have midges crawling across its "+
         "surface."));
   
    set_extraline("The narrow path you encountered before has reached a dead "+
       "end. To the south are trees and bushes surrounding a pond.");

    set_up_herbs( ({ HERB_DIR + "clove", HERB_DIR + "lothore", 
		     HERB_DIR + "ginger"}), 
		 ({"pond","trees","bushes","bush","tree","grass"}), 8);
    set_drink_from("pond");
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    BEACH;

    reset_room();
}

public void
init()
{
   ::init();
    init_drink();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Midge, NPC_DIR + "midge", 120.0 + rnd() * 120.0, LEB_DIR);
}
