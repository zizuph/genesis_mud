#include "defs.h"
inherit "/std/receptacle";

void
create_container()
{
    set_name("toolbox");
    add_name("box");
    set_pname("toolboxes");
    add_pname("boxes");
    set_short("wooden toolbox");
    set_pshort("wooden toolboxes");
    set_adj("wooden");
    set_long("It is a box for storing tools. It looks used, " +
        "solid.\n");

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_WEIGHT, 8000);
    add_prop(CONT_I_MAX_VOLUME, 4000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_VALUE, SILVER_VALUE * 2);
    add_prop(CONT_I_CLOSED, 1);
}
