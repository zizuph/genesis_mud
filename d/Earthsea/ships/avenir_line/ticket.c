inherit "/std/object";

#include "/sys/stdproperties.h"
#include "defs.h"

void
create_object()
{
    set_name("_gont_avenir_");
    add_name("ticket");
    add_adj("leaf");
    set_short("leaf ticket");
    set_long("This is a ticket for transport on a ship. "+
      "It seems to be a dried leaf of some kind.\n");
    add_prop(OBJ_I_VALUE, 24);
    add_prop(OBJ_M_NO_SELL, 1);
}
