/*
 *      /d/Gondor/arnor/fornost/s_square.c
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

static int     block();

static object *Ranger = allocate(2);

public void
create_fornost()
{
    set_short("a small square in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_rubble();
    add_ruins();
    add_street();
    add_item("stones",
        "The stones are all that is left of the buildings around the square.\n");
    add_item("square", 
        "There is little left of the square, but enough to be recognized as "+
    "such.\n");

    add_exit(FORNOST_DIR + "l_building", "west", 0, 3);
    add_exit(FORNOST_DIR + "archway", "northwest", block, 2);
    add_exit(FORNOST_DIR + "street", "south", 0, 3);
    add_exit(FORNOST_DIR + "plaza", "east", 0, 3);

    reset_room();
}

string
set_arnor_long()
{
    string desc;

    desc = "In a small square in the ruins of Fornost. "+
    "Tumbled stones lie scattered on the ground all over the square. "+
    "Some of the stones are "+
    "blackened as if some terrible heat made the very stones burn. Most "+
    "of the stones are covered by grass. A street leads south from here, "+
    "other exits are to the east and west. ";
    desc += query_arnor_time();

    return BSN(desc);
}

static int
block()
{
    if (TP->query_wiz_level())
    {
         write("This road is still closed for mortals, Wizard!\n");
         return 0;
    }
    write("That way is not open yet.\n");
    return 1;
}

public void
reset_room()
{
    clone_npcs(Ranger, NPC_DIR + "n_ranger", -1.0);
    Ranger->add_prop(OBJ_I_HIDE, 40 + random(21));
}
