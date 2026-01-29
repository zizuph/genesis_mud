inherit "/std/object";

#include "/sys/stdproperties.h"
#include "defs.h"

void
create_object()
{
    set_name("ticket");
    add_name("_gont_calia_");
    set_short("silvery ticket");
    set_long("This is a ticket for transport on a ship. "+
      "It is made of silvery paper.\n");
    add_prop(OBJ_I_VALUE, 24);
    add_prop(OBJ_M_NO_SELL, 1);
}
