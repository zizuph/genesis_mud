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
    set_areatype(AREATYPE_ROAD);
    set_area("northern");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The green coomb forms a great hollow in the mountains. "+
    "To the south the coomb climbs higher. The "+
    "road goes south and east. To the west the coomb becomes more hilly. "+
    "To the north are low hills. To the south there is a long dike. Beyond "+
    "the dike a gorge goes into the mountains.");

    COOMB;
    ROAD;
    PEAKS;
    COOMB_STREAM;
    GULLY;
    add_item("mountains","The mountains are high and the peaks "+
    "snow-covered.\n");
    add_item("dike",BS("You estimate the length of the dike to be half a mile, "+
    "covering the mouth of a gorge in a half-circle. \n"));
    add_item("gorge","Inside the gorge you can see a tower and some walls.\n");
    add_item(({ "walls", "tower" }), "No details can be seen from here.\n");
    add_item("hills", "The hills rise with long slopes.\n");

    add_exit(ROH_DIR+"horn/coomb/nw_coomb","west",0);
    add_exit(ROH_DIR+"horn/coomb/ne_coomb","east",0);
    add_exit(ROH_DIR+"horn/coomb/s_coomb","south",0);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("hills")),
                     HERB_DIR + "handasse", }),
                  ({ "ground", }), 3);
}

