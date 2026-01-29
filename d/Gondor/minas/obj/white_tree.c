/*
 *  /d/Gondor/minas/obj/white_tree.c
 *
 *  Dead tree in the Court of the Fountain 
 *
 *  Last modified by Alto, 06 April 2001
 *
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public int  kneel_tree();

create_object()
{
    set_name("tree");
    set_short("dead tree stands in the center of the pool");
    set_adj("dead");
    set_long("This dead tree seems very out of place amidst the "
        + "grandeur of the courtyard. The men of Gondor have "
        + "kept it here long after its death because it was a "
        + "descendant of the fair tree Nimloth in Numenor. This "
        + "tree passed with the death of Steward Belecthor II, and "
        + "no sapling has ever been found to replace it.\n");

    add_item(({"branches"}), "The branches on the tree are brittle "
        + "and broken. Drops of water from the fountain "
        + "fall sadly from the branches into the pool below.\n");
    add_cmd_item(({"tree", "before tree", "to tree", "dead tree",
        "before dead tree", "to dead tree"}), "kneel", &kneel_tree());

    add_prop(OBJ_M_NO_GET,1);
}

int
kneel_tree()
{
    object actor;

    actor = TP;

    write("You kneel reverently before the dead tree in the center "
        + "of the pool.\n");

    tell_room(environment(actor), QCTNAME(actor) + " kneels reverently "
        + "before the dead tree in the center of the pool.\n", ({actor}));

    return 1;
}
