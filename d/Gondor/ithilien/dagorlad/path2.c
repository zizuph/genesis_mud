#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"

void
create_area_room()
{
    set_areatype(9);
    set_areadesc("heathland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("To the east rise the Teeth of Mordor, the two towers " +
        "that guard the Morannon and the Cirith Gorgor, the entrance " +
        "into the black land. South of them stretches the Ephel Duath, " +
        "while further east the ridges of the Ered Lithui range.\n");
    add_item(({"mountains","mountain-range","mountain","ephel duath",
        "ered lithui"}), 
        "Upon the west of Mordor marches the gloomy ranger of the " +
        "Ephel Duath, the Mountains of Shadow, and upon the north, " +
        "the broken peaks and barren ridges of Ered Lithui, grey as " +
        "ash. But as these ranges approch one another, they swing out " +
        "large arms northward; and between these arms there is a deep " +
        "defile, Cirith Gorgor, the Haunted Pass, the entrance to the " +
        "Black Land.\n");
    add_item(({"teeth","tower","towers", "cirith gorgor"}),
        "Between the Ephel Duath and the Ered Lithui, there is a deep " +
        "defile, Cirith Gorgor, the Haunted Pass, the entrance to the " +
        "Black Land. High cliffs lower upon either side and thrust " +
        "forward from its mouth are two sheer hils, black-boned and " +
        "bare. Upon them stand the Teeth of Mordor, two towers strong " +
        "and tall and stony-faced, with dark window-holes staring " +
        "north and east and west, and each window full of sleepless " +
        "eyes. In the path there is a single gate of iron.\n");
    add_item(({"entrance", "morannon", "gate"}),
        "Across the mouth of the pass, from cliff to cliff, the Dark " +
        "Lord has built a rampart of stone. In it there is a single " +
        "gate of iron, and upon its battlements sentinels pace " +
        "unceasingly. That is the Morannon, the black gate of Mordor.\n");
    add_item(({"heath","heathland","heath land"}),
        "All about you lies a tumbled, barren heathland, grown with " +
        "few small shrubs. To the south, here and there knots of tall " +
        "pine-trees can be seen.\n");
    add_item(({"path"}), 
        "Across the heathland, a narrow path is running from north to " +
        "south. It looks like it has not been used for years.\n");
    add_exit(ITH_DIR + "dagorlad/path3", "north",     0, 3);
    add_exit(ITH_DIR + "dagorlad/path1", "south",     0, 3);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     HERB_DIR + "coccinea", }),
                  ({ "heath","wood","bushes"}), 5);

    FIX_EUID
    BLACK_RIDER_ROOM->load_me();
}

