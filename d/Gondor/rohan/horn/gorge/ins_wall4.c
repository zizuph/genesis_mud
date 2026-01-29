inherit "/d/Gondor/rohan/horn/helmsdeep.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void 
create_helmsdeep_room()
{
    set_short_desc("a field inside Helm's wall");
    set_extra_long("A field inside the wall. The wall runs from "+
    "southeast to northwest, and a path follows the wall. ");

    FIELD;
    GRASS;
    PATH;
    KEEP;
    CLIFFS;
    MOUNTAINS;
    add_item("wall","Helm's wall was built long ago by the sea-kings "+
    "from Gondor.\n");
    add_item( ({ "caves", "gorge" }),
	"You think you see some caves further up the gorge.\n");

    add_exit(ROH_DIR+"horn/gorge/ins_wall3","northwest",0);
    add_exit(ROH_DIR+"horn/gorge/ins_wall5","southeast",0);

    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs("meadow")),
		    ONE_OF_LIST(HERB_MASTER->query_herbs("plains")),
		    ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")), }),
		 ({ "field", "grass", }), 3);
}

