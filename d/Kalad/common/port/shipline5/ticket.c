inherit "/std/object";
#include "/sys/stdproperties.h"
#include "../default.h"

void
create_object()
{
    set_name("ticket");
    add_name("the kalad-emerald line");
    set_adj("emerald");
    add_adj("green");
    set_long("It looks like a ticket for the Kalad-Emerald shipline.\n");
    add_prop(OBJ_I_VALUE,24);
}

