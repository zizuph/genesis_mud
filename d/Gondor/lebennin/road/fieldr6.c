/*
 * /d/Gondor/lebennin/road/fieldr6.c
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
    add_exit(LEB_DIR + "road/fieldr8", "north", 0, 2);
    add_exit(LEB_DIR + "road/fieldr7", "east",  0, 2);
    add_exit(LEB_DIR + "road/fieldr5", "west",  0, 2);
   
    add_item(({"river","anduin"}), 
        "The river is to your east, but you cannot quite see the other side.\n");
    set_extraline("This field is just like the others around it, and stretches "+
       "out to the north, west, and east.");
   
    set_up_herbs( ({ HERB_DIR + "dill", HERB_DIR + "garlic", 
		     HERB_DIR + "attanar", }),
		  ({ "bushes","bush","plain","ground","grass"}), 8);
   
    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Rabbit, NPC_DIR + "wrabbit", 120.0 + rnd() * 120.0, LEB_DIR);
    (Rabbit - ({ 0 }))->set_random_move(5 + random(11));
}

