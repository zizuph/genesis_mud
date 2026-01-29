#pragma strict_types
inherit "/d/Gondor/common/lib/area_room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_GHOP 7

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
    set_extraline("You have strolled off the main road and now all "
      + "around you are bushes. South, the river Erui blocks all "
      + "progress.");
    add_exit(LEB_DIR + "road/nr5","north", 0, 2);
   
    add_item(({"bush","bushes"}), "These bushes are crawling with insects.\n");
    add_item(({"river","erui"}),"This is the river Erui, blocking your way south.\n");

    reset_room();

    set_up_herbs( ({ HERB_DIR + "ginger", HERB_DIR + "chervil",
		     HERB_DIR + "caraway", }),
		  ({ "bushes","bush","plain","plains","ground","grass"}), 8);
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(GHop, NPC_DIR + "grasshopper", 60.0 + rnd() * 120.0,
	       LEB_DIR);
    ONE_OF_LIST(GHop - ({ 0 }))->set_random_move(10 + random(11));
}
