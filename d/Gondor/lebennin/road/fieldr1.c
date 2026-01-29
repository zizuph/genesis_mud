/*
 *	/d/Gondor/lebennin/road/fieldr1.c
 *
 *	Modification log:
 *	 05/06/96, Arren:	Updated code.
 *	29-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_GHOP 7

public void    reset_room();

static object *GHop = allocate(MAX_GHOP);

public void
create_area_room()
{
   set_area("northeast");
   set_areaname("Lebennin");
   set_land("Gondor");
   set_areatype(2);
   set_areadesc("field");
   set_grass("green");
   
   add_exit(LEB_DIR + "road/nr10",    "northwest", 0, 2);
   add_exit(LEB_DIR + "road/fieldr2", "east",      0, 2);
   
   set_extraline("You have strolled off the main road and now all around "+
		 "you are bushes, but a narrow path leads east.");
   
   add_item(({"bush","bushes"}),"These bushes are crawling with insects.\n");
   add_item(({"path","trail"}), 
         "The narrow path leads east through a space in the bushes.\n");
   
   set_up_herbs( ({ HERB_DIR + "astaldo", HERB_DIR + "saffron", 
		    HERB_DIR + "tuo"}), 
		({"bushes","bush","plain","ground","grass"}), 6);

   reset_room();
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(GHop, NPC_DIR + "grasshopper", 180.0 + rnd() * 180.0, LEB_DIR);
    (GHop - ({ 0 }))->set_random_move(1);
}
