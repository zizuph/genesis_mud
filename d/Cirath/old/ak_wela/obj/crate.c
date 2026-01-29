/*
 * The crates in the warehouse near the piers of Ak Wela.
 * Easily robbed, but it isn't usually worth much.
 */

inherit "/std/container";

#include "/d/Cirath/common/defs.h"

void
create_container()
{
    set_short("large, wooden crate");
    set_long("@@my_long@@");
    set_name("crate");
    add_name("box");
    set_adj("large");
    add_adj("wooden");

    add_prop(OBJ_M_NO_GET, "It's too large and heavy for you.");
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_RIGID, 1);
}
