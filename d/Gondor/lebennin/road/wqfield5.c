/*
 * /d/Gondor/lebennin/road/wqfield5.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 * Changed inheritance, general revision - 6-Feb-1997, Olorin.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_GHOP 5

static object *GHop = allocate(MAX_GHOP);

public int
enter()
{
    write("Cautiously, you crawl into the dark opening, not knowing what to expect.\n");
    return 0;
}

public void
create_area_room()
{
    string *herbs;

    set_area("northeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(5);
    set_areadesc("small glen");
    set_grass("sparse");
   
    add_exit(LEB_DIR + "wolfcave/cave1", "northwest", enter, 2);
    add_exit(LEB_DIR + "road/wqroad5",   "southwest",     0, 2);
   
    set_extraline("Low hills covered by sparse grass " +
        "and small bushes surround you " +
      "almost completely. Only to the southwest you can see a narrow road " +
      "passing the glen. Further north, the highest peaks of the White Mountains " +
      "raise their snowcovered heads above the hills around you. " +
      "Under an overhanging rock of the hill to the northwest, you can see a dark opening.");
    add_item(({"peaks","peak","white mountains","ered nimrais","mountains","mountain"}),    
      BSN("Some of the peaks of the Ered Nimrais are visible from here, "+
      "but most are hidden by the hills all around you."));
    add_item(({"grass","bushes","bush"}), BSN(
      "Only a few small bushes and thin grass growing sparsely can be seen on the " +
      "rocky flanks of the hills surrounding you."));
    add_item(({"road","path"}), 
      "More of a path than a road, winding towards the hills further into the mountains.\n");
    add_item("ground","The ground is rocky here, and hardly covered by the sparse grass.\n");
    add_item(({"rock","overhanging rock","opening","dark opening","flank"}), BSN(
      "Under an overhanging rock on the hill towards the northwest, you " +
      "can see a dark opening. It could lead into a small cave, probably " +
      "the den of some animals."));
    add_item(({"hill","hills","foothills","glen"}), BSN(
      "This small glen is surrounded on almost all sides by some rocky " +
      "foothills of the White Mountains. There is only a little vegetation " +
      "here, and further north it is even scarcer. The steepest " +
      "hill is to the northwest, where you notice a dark opening under an " +
      "overhanging rock."));

    herbs = HERB_MASTER->query_herbs("meadow");
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 4913),
		     ONE_OF_LIST_WITH_SEED(herbs, 4914),
		     ONE_OF_LIST_WITH_SEED(herbs, 4915), }),
		 ({"grassland","bush","plain","field","ground","grass"}), 5);
    reset_room();
}

public void
reset_room()
{
   ::reset_room();

   clone_npcs(GHop, NPC_DIR + "grasshopper", 180.0, LEB_DIR + "road/");
}

