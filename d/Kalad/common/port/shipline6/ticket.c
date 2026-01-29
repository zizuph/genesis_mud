inherit "/std/object";
#include "/sys/stdproperties.h"
#include "../default.h"

void
create_object()
{
    set_name("ticket");
    add_name("the kabal-raumdor line");
    set_adj("tattered");
    set_short("tattered ticket");
    set_long("It looks like a ticket for the Kabal-Raumdor shipline.\n");
    add_prop(OBJ_I_VALUE,24);
}

