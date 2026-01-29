inherit "/std/object.c";
#include "/d/Emerald/outpost1/defs.h"

void
create_object()
{
    set_name("table");
    set_adj("wooden");
    add_adj("long");
    set_short("long wooden chair");
    set_long("This table is made from flattened wooden logs. It looks " +
        "quite sturdy, and is rather large\n");
    add_prop(OBJ_M_NO_GET, 1);
}
