inherit "/std/object";

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("ticket");
    add_name(SPARKLE_LINE);
    add_adj("brand");
    add_adj("new");
    set_long("It looks like a ticket to some ship.\n");
    add_prop(OBJ_I_VALUE, 24);
}

query_recover()   { return MASTER; }
