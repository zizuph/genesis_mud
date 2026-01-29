/*
 * The table in the Palantir Chamber of the White Tower.
 *
 * /d/Gondor/minas/obj/palantir_table.c
 *
 * Alto, 01 April 2001
 *
 */


inherit "/std/container";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

object palantir;

void
create_container()
{
    set_short("small round table");
    set_name("table");
    add_name("small table");
    add_name("small round table");
    set_adj("small");
    add_adj("round");
    set_long("This is a small round table made of native stone. In fact, "
        + "it appears to grow right out of the stone of the floor. The "
        + "table is shaped like a tree, with small many-rayed stars "
        + "seeming to twinkle on the periphery.\n");

    add_item(({"stars", "many-rayed stars"}), "They seem to twinkle on "
        + "the periphery of the table.\n");

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

    palantir = clone_object(INNER_MINAS + "/obj/palantir.c");
    palantir->move(TO);


}

