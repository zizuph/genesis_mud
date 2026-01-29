/*
 * The tomb of Ecthelion II.
 *
 * /d/Gondor/minas/obj/ecthelion_table.c
 *
 * Alto, 1 June 2001
 *
 */


inherit "/std/container";

#include "/d/Gondor/minas/lib/porter_defs.h"
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"


void
create_container()
{
    set_short("first table");
    set_name("table");
    set_adj("first");
    set_long("On the first table is inscribed Ecthelion II, "
        + "Steward of Gondor.\n");

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

