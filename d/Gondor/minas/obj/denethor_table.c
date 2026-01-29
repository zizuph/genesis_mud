/*
 * The tomb of Denethor II.
 *
 * /d/Gondor/minas/obj/denethor_table.c
 *
 * Alto, 1 June 2001
 *
 */


inherit "/std/container";

#include "/d/Gondor/minas/lib/porter_defs.h"
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

object crop, mallet, rake;


void
create_container()
{
    set_short("second table");
    set_name("table");
    set_adj("second");
    set_long("On the second table is inscribed Denethor II, "
        + "Steward of Gondor. Unlike the other tables, however, this "
        + "one does not have the body of a steward resting upon it, but "
        + "is instead empty.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The table is far too heavy to pick up.\n");
    add_prop(OBJ_I_VOLUME,      1000);
    add_prop(OBJ_I_WEIGHT,      1000);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_WEIGHT,     2000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_ATTACH,    1);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(from))
    {
    return;
    }

    if (ob->id("_denethor_q_bundle_"))
    {
        from->add_prop(DELIVERED_DENETHOR_BUNDLE, 1);
        return;
    }
    return;
}

