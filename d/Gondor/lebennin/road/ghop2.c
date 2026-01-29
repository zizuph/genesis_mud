#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

#define MAX_GHOP 7

static object *GHop = allocate(MAX_GHOP);

public void
create_road()
{
    set_area("northeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");
    set_extraline("You have strolled off the main road and now all "
     + "around you are bushes. You see a large mound directly to your "
     + "south, while to the north you can see the Ered Nimrais.");

    add_exit(LEB_DIR + "road/nr4","north", 0, 2);

    add_white_mountains("north");
    add_item( ({ "mound", "hill", }), BSN(
        "A large mound, almost a small hill, fills the view to the " +
        "south. Bushes and small trees are growing on it, and somehow " +
        "it gives the impression that it has been there for a long, long " +
        "time, perhaps centuries, perhaps even longer."));
    add_item(({"bush","bushes"}), "These bushes are crawling with insects.\n");
    add_item(({"grass"}), 
       "The grass is as green as you have ever seen green.\n");

    set_up_herbs( ({ HERB_DIR + "ginger", HERB_DIR + "athelas",
		     HERB_DIR + "caraway"}),
		  ({ "bushes","bush","plain","plains","ground","grass"}),
                  8);
    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(GHop, NPC_DIR + "grasshopper", 60.0 + 120.0 * rnd(),
		LEB_DIR);
    ONE_OF_LIST(GHop - ({ 0 }))->set_random_move(5 + random(11));
}
