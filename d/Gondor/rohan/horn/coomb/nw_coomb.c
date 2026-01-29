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
    set_areatype(0);
    set_area("northwestern");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The green coomb forms a great hollow in the mountains. "+
		  "To the west and north the "+
    "hills become higher. Further east is the mouth of "+
    "the coomb; south, the coomb continues to the mountains.");

    COOMB;
    COOMB_MOUNTAINS;
    PEAKS;
    add_item("hills", "The hills rise with long slopes.\n");

    add_exit(ROH_DIR+"horn/coomb/n_coomb","east",0);
    add_exit(ROH_DIR+"horn/coomb/sw_coomb","south",0);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("hills")),
                     HERB_DIR + "basil", }),
                  ({"coomb", }), 3);
}
