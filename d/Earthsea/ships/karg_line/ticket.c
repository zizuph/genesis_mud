inherit "/std/object";

#include "/sys/stdproperties.h"
#include "defs.h"

void
create_object()
{
    set_name("ticket");
    add_name("_gont_karg_");
    set_short("dirty ticket");
    add_adj("dirty");
    set_long("This is small and dirty ticket.\n");
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_M_NO_SELL, 1);
}
