inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("ticket");
    add_name("Faerun1");
    add_adj("brand");
    add_adj("new");
    set_long("'Brevari' is printed on the topside of the ticket.\n");
    add_prop(OBJ_I_VALUE, 24);
}

query_recover()   { return MASTER; }
