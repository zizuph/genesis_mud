#pragma strict_types
inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_area_room()
{
    set_areatype(2);
    set_areadesc("heathland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The mountains loom up to the east, but between at the " +
        "foot of the slopes is the road that runs south from the " +
        "Morannon. All around is a tumbled heathland grown with shrubs.\n");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),	
        "The mountains named Ephel Duath lie like a dark shadow on the "+
        "road. You judge the mountains to be between 5000 to 7000 feet "+
        "tall. The roots of the hills are rising next to the road " +
        "and are covered with sombre trees like dark clouds.\n");
    add_item("road",
        "The long straight road runs north towards the Morannon, " +
        "the Black Gates of Mordor, while in the other direction it " +
        "goes to the crossroads where it meets the road from Osgiliath " +
        "to Minas Morgul. The handiwork of the Men of old can still be " +
        "seen in its straight sure flight and level course.\n");
    add_item(({"forest","wood","woods","trees","knots"}),
        "On the heathland knots of pine-trees are growing, that " +
        "become more numerous and denser towards the south. There fir, " + 
        "cedar, cypress, and other resinous trees join the pines.\n");
    add_item(({"heath","shrub","shrubs","heathland","heath land"}),
        "All about you lies a tumbled heathland, grown with ling and " +
        "broom and cornel, and other shrubs you do not know. Here " +
        "and there knots of tall pine-trees can be seen. " +
        "To the south, these knots become more numerous, with fir and " +
        "cedar and cypress mingling with the pine-trees.\n");
    add_item(({"path"}),
        "Across the heathland, a narrow, overgrown path is running " +
        "from the southwest to the north. It looks like it has not " +
        "been used for years.\n");
    add_exit(ITH_DIR + "road/nr11",      "southeast", 0, 3);
    add_exit(ITH_DIR + "dagorlad/path2", "north",     0, 3);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     HERB_DIR + "suranie", }),
                  ({"heath","wood","bushes"}), 4);
}

