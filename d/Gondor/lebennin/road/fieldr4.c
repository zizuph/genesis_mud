/*
 * /d/Gondor/lebennin/road/fieldr4.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 *  3-Feb-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_RAB 2

static object *Rabbit = allocate(MAX_RAB);

public void
create_area_room()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");

    add_exit(LEB_DIR + "road/fieldr5", "east", 0, 2);
    add_exit(LEB_DIR + "road/nr17",    "west", 0, 2);
   
    add_item(({"ground","field"}), 
         "The field is littered with rabbit tracks and rabbit poop.\n");
    add_item(({"anduin","river"}), 
         "The river Anduin to your east flows deep and wide towards the sea.\n");
    add_item(({"pelargir","city"}), 
         "The city of Pelargir is comfortingly close. You feel protected here.\n");
   add_item(({"road","roads"}), 
         "The road to your west is quite old.\n");
   
    set_extraline("The main road is just to your west, and east you feel "+
        "safe walking in these fields so close to Pelargir. The river is"+
        " a bit to the east, and here you can see rabbits hopping about.");

    set_up_herbs( ({ HERB_DIR + "garlic", 
		     ONE_OF_LIST(HERB_MASTER->query_herbs("lebennin")), }),
		  ({ "grass","bush","bushes","ground"}), 8);
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Rabbit, NPC_DIR + "wrabbit", 120.0 * rnd() * 120.0, LEB_DIR);
    (Rabbit - ({ 0 }))->set_random_move(5 + random(11));
}
