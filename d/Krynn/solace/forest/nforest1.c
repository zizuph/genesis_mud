/* Forest coded by Lord Rastlin */
/* modified by Teth, Feb.13,96 */
#include "local.h"

inherit FOROUTROOM;

#include "/d/Krynn/common/defs.h"
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"mixedforest", }) );

void
reset_solace_room()
{
    set_searched(random(2));
}


void
create_solace_room()
{
    set_place(FOREST);

    set_long_desc("Looking about you, you recognize the woods as those " +
             "near Solace, which would place you in the proximity of " +
             "Near Fields. To the east and far south rest foothills " +
             "of the small Sentinel Peaks mountain range. A path leads " +
             "north to Northfields, and also south, to Solace.");
    add_item(({"foothills","hills","mountain range","mountains",
               "Sentinel Peaks", "sentinel peaks", "Peaks", "peaks"}),
               "These surround you, giving the area a measure of " +
               "distinction.\n");
    add_item("Near Fields", "You aren't there yet, so there's not much " +
             "to see.\n");
    add_item(({"forest","woods"}), "Here it surrounds you, but it seems to " +
             "open up towards the north. It is mainly composed of pine, " +
             "birch, and poplar trees.\n");
    add_item(({"pine trees", "poplar trees", "birch trees", "trees"}),"The " +
             "trees stand tall and healthy, all competing for sunlight and " +
             "space.\n");
    add_item("path", "This well-travelled path seems to be the local route " +
             "from Northfields to Solace. Herbs grow at the side of the " +
             "rough road.\n");
    add_exit(TDIR + "nforest3", "south");
    add_exit(NEWSEA, "north");
 
    reset_room();
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","path",}), 2);
}

