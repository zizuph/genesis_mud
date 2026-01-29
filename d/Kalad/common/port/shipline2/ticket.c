inherit "/std/object";
#include "/sys/stdproperties.h"
#include "../default.h"

void
create_object()
{
    set_name("ticket");
    add_name("the kalad-terel line");
    set_adj("dark");
    add_adj("blue");
    set_long("It looks like a ticket for the Kalad-Terel shipline.\n");
    add_prop(OBJ_I_VALUE,24);
}

