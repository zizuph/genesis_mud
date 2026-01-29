/*
 *      /d/Gondor/arnor/fornost/look_out.c
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

string query_tower_view();

static object  Ranger;

public void
create_fornost()
{
    set_short("on top of a grey tower outside the ruins of Fornost");

    add_hills();

    add_item(({ "battlement", "parapet" }),
        "Between the merlons are clefts through which men can shoot.\n");
    add_item("view", query_tower_view);
    add_item("village", "You guess that it is Bree.\n");
    add_item(({ "ruins", "fornost "}), "It was once a fortress city.\n");
    add_item("swamp", "The marshy plain extends far to the south. You "+
        "see many puddles and pools.\n");
    add_item(({ "plains", "woods" }), "It is too far to see any details.\n");
    add_item("tower", "It is a watchtower, from here you can see far.\n");
    add_item(({ "staircase", "stairs" }),
        "A narrow staircase made of stone.\n");
    add_item(({ "clefts", "embrasures" }),
        "Opening in parapet between two merlons.\n");
    add_item("merlons", "Solid part of battlement between two embrasures.\n");

    add_exit(FORNOST_DIR + "ins_g_tow", "down", 0, 1);
}

string
set_arnor_long()
{
    string desc;

    desc = "On top of a round grey tower. "+
    "A battlement runs around the edge of the tower. There is a grand view "+
    "all around. Stairs are going down. ";
    desc += query_arnor_time();

    return BSN(desc);
}

string
query_tower_view()
{
    string desc;

    desc = "To the north you see the hills of the North Downs. "+
    "West, below you, are the grass covered ruins of Fornost. "+
    "And looking east you see small woods on a plain. "+
    "To the south is a swamp. ";
    if (TP->query_race() == "elf")
        desc += "Beyond the swamp you see a village.";
    return BSN(desc);
}
 
public void
reset_room()
{
    Ranger = clone_npc(Ranger, NPC_DIR + "n_ranger");
}
