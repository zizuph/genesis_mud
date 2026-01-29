#pragma strict_types

inherit "/d/Gondor/rohan/horn/helmsdeep.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void cross_stream();

void
create_helmsdeep_room()
{
    set_short_desc("Outside the Deeping-wall");
    set_extra_long("Outside the Deeping-wall. "+
    "The wall ends here at the base of the Rock here; "+
    "a battlement juts over the top of the wall. ");

    KEEP;
    STREAM;
    GULLY;
    ROCK;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item(({"parapet","battlement"}),BSN("The parapet protects the top "+
    "of the wall, here and there are clefts in the stone through which "+
    "archers can shoot. Nothing more can be seen from this side."));
    add_item(({ "wall", "deeping-wall", "deeping wall" }), BSN(
    "The wall is perhaps twenty feet high, and the top is sheltered by "+
    "a parapet. The front is smooth and the great stones are set "+
    "with such skill that no foothold can be found."));

    add_exit(ROH_DIR+"horn/gorge/out_wall2", "southeast", cross_stream, 5);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("plain")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("meadow")), }),
        ({ "field", "ground", "gorge", }), 5);
}

void
cross_stream()
{
    write("You cross the stream.\n");
}
