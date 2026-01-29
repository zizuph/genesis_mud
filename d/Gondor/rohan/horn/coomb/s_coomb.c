#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

public void
create_area_room()
{
    set_areadesc("hill");
    set_areatype(8);
    set_area("southern");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The green coomb forms a great hollow in the mountains. "+
    "The coomb continues to the west, north and east. Beside the road a "+
    "stream gently flows to the north. To the south, a long dike extends "+
    "in a half-circle, protecting the mouth of a gorge leading "+
    "into the mountains. Inside the gorge there is a keep with a "+
    "lofty tower upon a heel of rock, thrusting outward from the "+
    "cliffs.");

    COOMB;
    COOMB_MOUNTAINS;
    PEAKS;
    COOMB_STREAM;
    GULLY;
    GORGE;
    KEEP;
    ROCK;
    FIELD;
    GRASS;
    CLIFFS;
    add_item("tower", "The tower rises high upon the rock; no "+
    "details can be seen from here.\n");
    add_item( ({ "dike", "breach" }),
    "There is a breach in the dike to the south.\n");

    add_exit(ROH_DIR + "horn/coomb/n_coomb", "north", 0);
    add_exit(ROH_DIR + "horn/coomb/sw_coomb", "west", 0);
    add_exit(ROH_DIR + "horn/coomb/se_coomb", "east", 0);
    add_exit(ROH_DIR + "horn/gorge/breach", "south", 0);

    set_up_herbs( ({ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
		    ONE_OF_LIST(HERB_MASTER->query_herbs("hills")),
                    HERB_DIR + "bpotato", }),
                  ({"coomb", "field", "fields", "grass", "ground", }), 3);
}

