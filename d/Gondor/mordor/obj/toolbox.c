/*
 * /d/Gondor/mordor/obj/toolbox.c
 *
 * This is a box, too heavy or large to get, but a lot of things might be
 * put in it.
 *
 * /Mercade, 26 October 1993
 *
 * Revision history:
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/*
 * Called to create the chest.
 */
void
create_container()
{
    set_name("toolbox");
    add_name("box");
    add_name("_toolbox_at_cirith_ungol_");
    set_pname("toolboxes");
    add_pname("boxes");
    set_short("wooden toolbox");
    set_pshort("wooden toolboxes");
    set_adj("tool");
    set_adj("wooden");
    set_long(BSN("It is a wooden toolbox. It looks quite old, but it is " +
        "still quite strong. Orcs use this box to put tools in."));

    add_item( ({ "band", "bands", "iron band", "iron bands" }),
        BSN("Several iron bands are fastened to the box to make it " +
        "stronger than it already is."));
    add_item("lock", BSN("This box does not have a lock."));

    set_cf(TO);

    add_prop(CONT_M_NO_REM, "@@can_approach_container");
    add_prop(CONT_M_NO_INS, "@@can_approach_container");
    add_prop(OBJ_M_NO_GET,  "@@can_approach_container");
    add_prop(CONT_I_WEIGHT,      20000);
    add_prop(CONT_I_VOLUME,      20000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(CONT_I_MAX_VOLUME, 120000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_VALUE, 150 + random(50));
    add_prop(CONT_I_CLOSED, 1);
}

/*
 * Open/close protection: are there any orcs present.
 */
int
open()
{
    object orc = (object)ENV(TP)->query_living_orc();

    if (((ENV(TO)) == (ENV(TP))) && (objectp(orc)))
    {
        write(BSN("The " + check_call(orc->short()) + " stops you from " +
            "touching the " + short() + "."));
        return 1;
    }

    return 0;
}

int
close()
{
    return open();
}

/*
 * This procedure will refrain people from inserting stuff into the container
 * or remove stuff from it if there is an orc present in the room.
 */
mixed
can_approach_container()
{
    object orc = (object)ENV(TP)->query_living_orc();

    if (((ENV(TO)) == (ENV(TP))) && (objectp(orc)))
    {
        return BSN("The " + check_call(orc->short()) + " stops you from " +
            "touching the " + short() + ".");
    }

    return 0;
}

/*
 * Stuff for recovery
 */
string query_recover()
{
    return MASTER + ":" + query_container_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
}
