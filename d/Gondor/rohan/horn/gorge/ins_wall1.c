#pragma strict_types

inherit "/d/Gondor/rohan/horn/helmsdeep.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void 
create_helmsdeep_room()
{
    string *herbs;

    set_short_desc("A field inside Helm's wall");
    set_extra_long("A field inside the wall. The wall runs from "+
    "southeast to northwest. A path follows the wall, and "+
    "the Rock rises up to the northwest. A stairway leads up to the "+
    "top of the wall and to the west another path leads to the rear-gate. ");

    FIELD;
    GRASS;
    PATH;
    KEEP;
    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("wall", "Helm's wall was built long ago by the sea-kings "+
    "from Gondor.\n");
    add_item("rock","The keep is built on the Rock.\n");

    add_exit(ROH_DIR + "horn/gorge/ifield","west",0);
    add_exit(ROH_DIR + "horn/gorge/ins_wall2","southeast",0);
    add_exit(ROH_DIR + "horn/on_walls/h_wall1","up",0,2);

    herbs = HERB_MASTER->query_herbs( ({ "rohan", "plains", "hills", }));
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 841023),
		     ONE_OF_LIST_WITH_SEED(herbs, 701536),
		     ONE_OF_LIST_WITH_SEED(herbs, 375235), }),
		  ({ }), 5);
}

