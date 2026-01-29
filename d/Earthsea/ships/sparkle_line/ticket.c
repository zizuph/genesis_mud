inherit "/std/object";

#include "/sys/stdproperties.h"
#include "defs.h"

void
create_object()
{
    set_name("ticket");
    add_name("_gont_sparkle_");
    set_short("feathery ticket");
    add_adj("feathery");
    set_long("This is a ticket for transport on a ship. "+
      "It looks very much like the feather of some bird, "+
      "however.\n");
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_M_NO_SELL, 1);
}
