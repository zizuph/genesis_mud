/*
 *      /d/Gondor/arnor/fornost/south_ridge.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_fornost()
{
    set_short("at the southern end of a ridge between two hilltops");

    add_grass();
    add_hills();

    add_item("ridge",
    "The ridge is connecting the southern hill with the other hills "+
    "spreading out northeast.\n");
    add_item(({ "plains", "woods" }),
    "The plains and woods spread out to the east as far as you can see.\n");
    add_item(({ "ruins", "fornost" }),"It was once a fortress city.\n");
    add_item("hilltop", "You have to move closer to it to make out any details.\n");

    add_exit(FORNOST_DIR + "middle_ridge", "north", 0, 2);
    add_exit(FORNOST_DIR + "on_hill", "south", 0, 2);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("hills")),
                         HERB_DIR + "madwort", 
                         HERB_DIR + "frostheal", }),
        ({"ridge", "hills", "hill", "grass", }), 5);
}

string
set_arnor_long()
{
    string desc;

    desc = "In the southern end of a grassy ridge between two hilltops. "+
    "The ridge slopes steeply down to the west and east. To the west, "+
    "below you, are the ruins of Fornost. Looking east you see woods and "+
    "plains. The ridge extends to the north, south is a hilltop. ";
    desc += query_arnor_time();
    desc += "\n";

    return desc;
}

