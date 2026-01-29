inherit "/std/object.c";
#include "/d/Emerald/outpost1/defs.h"

void
create_object()
{
    set_name("bench");
    set_adj("wooden");
    add_adj("simple");
    set_short("simple wooden bench");
    set_long("This bench is made from de-barked wooden logs, it looks " +
        "sturdy but not very comfortable.\n");
    add_prop(OBJ_M_NO_GET, 1);
}
