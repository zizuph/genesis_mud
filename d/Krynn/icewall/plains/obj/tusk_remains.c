inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("tusk");
   add_name("_thanoi_tusk");
   set_adj("thanoi");
   set_short("thanoi tusk");
   set_long("The tusks of a thanoi are made of solid bone, several inches thick, " +
        "and grow to a length of nearly three feet in the largest adults.\n");
   add_prop(OBJ_I_VOLUME, 80);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VALUE, 100);
}

