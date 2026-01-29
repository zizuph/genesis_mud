#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

public void
create_area_room()
{
    set_areadesc("steep slope");
    set_areatype(0);
    set_area("southeastern");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The green coomb forms a great hollow in the mountains. "+
    "North is the mouth "+
    "of the coomb, to the east and south are mountains "+
    "and to the west there is a road beside a stream. ");

    COOMB;
    COOMB_MOUNTAINS;
    PEAKS;
    COOMB_STREAM;
    GULLY;
    ROAD;
    add_item("dike",BS("You estimate the length of the dike to be half a mile, "+
    "covering the mouth of a gorge in a half-circle. \n"));
    add_exit(ROH_DIR + "horn/coomb/ne_coomb", "north", 0, 2);
    add_exit(ROH_DIR + "horn/coomb/s_coomb",  "west",  0, 2);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("plain")),
                      HERB_DIR + "suranie", }),
                    ({"slope", "grass", }), 3);
}

