inherit "std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("table");
    set_short("oak table");
    add_adj(({"oak", "dinner", }));
    set_long(BSN("This table is incredibly long, almost to the point of "+
       "absurdity. There is place for about thirty place settings at the "+
       "table but there are only six chairs at it."));
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,200000);
}

