inherit "/std/object";

#include "../defs.h"

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("ticket");
    add_name(NORTH_SHORE_LINE);
    add_adj("crumpled");
    add_adj("brown");
    set_long("It looks like a ticket to some ship.\n");
    remove_prop(OBJ_I_VALUE);
}

query_recover()   { return MASTER; }

