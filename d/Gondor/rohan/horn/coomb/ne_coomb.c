#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

public void
create_area_room()
{
    set_areadesc("mouth of coomb");
    set_areatype(8);
    set_area("northeastern");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The green coomb forms a great hollow in the mountains. "+
    "The road turns west here. A small stream runs beside the road. "+
    "To the north the Vale spreads out. Beyond, the plains of Rohan reaches "+
    "the horizon. ");

    COOMB;
    ROAD;
    COOMB_MOUNTAINS;
    PEAKS;
    GULLY;
    add_item("stream","The Deeping-stream is lazy here.\n");
    add_item("vale","The Westfold Vale is rich and green.\n");
    add_item("ground","You see nothing special.\n");

    add_exit(ROH_DIR+"horn/coomb/high_vale","north",0);
    add_exit(ROH_DIR+"horn/coomb/se_coomb","south",0);
    add_exit(ROH_DIR+"horn/coomb/n_coomb","west",0);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("plain")),
                     HERB_DIR + "curugwath", }),
                  ({ "ground", "vale", }), 3);
}

