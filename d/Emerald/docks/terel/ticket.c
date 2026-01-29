inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("ticket");
    add_name("the emerald line2");
    add_adj("torn");
    set_long("It looks like a ticket to some ship.\n");
    add_prop(OBJ_I_VALUE, 18);
}

public string
query_recover()  { return MASTER; }
