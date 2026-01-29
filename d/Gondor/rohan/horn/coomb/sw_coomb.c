#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

public void
create_area_room()
{
    set_areadesc("slope");
    set_areatype(0);
    set_area("southwestern");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The green coomb forms a great hollow in the mountains. "+
		  "Further south the mountains "+
    "rise high and west the hills are rather low. North the Coomb "+
    "continues. To the east a road can be seen.");

    add_exit(ROH_DIR+"horn/coomb/nw_coomb","north",0);
    add_exit(ROH_DIR+"horn/coomb/s_coomb","east",0);

    COOMB;
    ROAD;
    COOMB_MOUNTAINS;
    PEAKS;
    add_item("dike",BS("You estimate the length of the dike to be half a mile, "+
    "covering the mouth of a gorge in a half-circle. \n"));
    add_item("hills", "The hills rise to the west with long slopes.\n");
    add_item("slope", "A green slope in the lower part of the hills.\n");

     set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
		      ONE_OF_LIST(HERB_MASTER->query_herbs("hills")),
		      HERB_DIR + "coccinea", }),
                   ({ "slope", }), 3 );
}
