inherit "/std/object";
#include "/sys/stdproperties.h"
#include "../default.h"

void
create_object()
{
    set_name("ticket");
    add_name("the kalad-city line");
    set_adj("silver-lined");
    set_long("It looks like a ticket for the Kalad-City shipline.\n");
    add_prop(OBJ_I_VALUE,30);
}

