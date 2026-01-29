inherit "/std/object";
#include "/d/Kalad/defs.h"

/* sarr */

void
create_object()
{
    set_name("dressers");
    set_adj("wooden");
    set_short("set of wooden dressers");
    set_long("There are where the guards keep their clothes stored. "+
    "They are all locked and shut tight.\n");
    add_prop(OBJ_M_NO_GET,"Are you the incredible hulk?\n");
}

