inherit "/d/Gondor/rohan/horn/helmsdeep.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void 
create_helmsdeep_room()
{
    set_short_desc("a field inside Helm's wall");
    set_extra_long("A field inside the wall. A path follows the wall "+
    "northwest, and a cliff rises to the southeast. "+
    "A stairway leads up to the top of the wall. ");

    FIELD;
    GRASS;
    PATH;
    KEEP;
    STAIRS;
    GORGE;
    MOUNTAINS;
    add_item("wall","Helm's wall was built long ago by the sea-kings "+
    "from Gondor.\n");
    add_item(({"cliff","southern cliff"}),"The cliff is high and steep, "+
    "impossible to climb.\n");

    add_exit(ROH_DIR + "horn/gorge/ins_wall4",  "northwest",0);
    add_exit(ROH_DIR + "horn/on_walls/h_wall5", "up",0,2);

    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs("meadow")),
		    ONE_OF_LIST(HERB_MASTER->query_herbs("plains")),
		    ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")), }),
		 ({ "field", "grass", }), 3);
}

