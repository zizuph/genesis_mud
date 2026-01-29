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

    set_short_desc("outside the Deeping-wall");
    set_extra_long("Outside the Deeping-wall. "+
    "The wall ends here at the base of the southern cliff; "+
    "a battlement juts over the top of the wall. ");

    add_item(({"parapet","battlement"}), BSN("The parapet protects the top "+
    "of the wall; here and there are clefts in the stone through which "+
    "archers can shoot. Nothing more can be seen from this side."));
    add_item(({ "wall", "deeping-wall", "deeping wall" }), BSN(
    "The wall is twenty feet high, and its top is sheltered "+
    "by a parapet. The front is smooth and the great stones are set "+
    "with such skill that no foothold can be found. On top of the wall "+
    "is a small tower."));
    add_item("cliff", "The cliff is high and smooth, impossible to climb.\n");
    WALLTOWER;
    GORGE;
    MOUNTAINS;

    add_exit(ROH_DIR + "horn/gorge/out_wall3", "northwest", 0);

    herbs = HERB_MASTER->query_herbs( ({ "rohan", "plains", "hills", }));
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 952841),
		     ONE_OF_LIST_WITH_SEED(herbs, 888155),
		     ONE_OF_LIST_WITH_SEED(herbs, 960447), }),
		  ({ }), 5);
}

