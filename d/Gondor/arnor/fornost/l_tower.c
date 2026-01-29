/*
 *      /d/Gondor/arnor/fornost/l_tower.c
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

static string  do_enter();

public void
create_fornost()
{
    set_short("at a ruined tower in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_ivy();
    add_rubble();
    add_ruins();
    add_stones();

    add_item(({ "tower", "ruined tower" }),
        "It is made of grey stone. There is an entrance leading into the tower.\n");
    add_item(({ "foundation", "mound" }), BSN(
        "It is the foundation of a tower. It probably was as large as the "+
        "other tower. Only a mound is now left of the foundation."));
    add_item("entrance", "You can enter the tower through the entrance.\n"); 

    add_cmd_item("tower", "enter", do_enter);

    add_exit(FORNOST_DIR + "plaza", "north", 0, 3);
    add_exit(FORNOST_DIR + "gate",  "southwest", 0, 3);
}

string
set_arnor_long()
{
    string desc;

    desc = "At a ruined tower in the ruins of Fornost. "+
    "The tower was once large but is now ruined above the first floor. "+
    "Ivy grows on the tower. Beside the tower is the remains of a "+
    "foundation. Exits are to the southwest and north. An open entrance "+
    "leads into the tower. ";
    desc += query_arnor_time();

    return BSN(desc);
}

static string
do_enter()
{
    set_dircmd("tower");
    TP->move_living("into the tower", FORNOST_DIR + "hideout_entr");
    return "";
}

