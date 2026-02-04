inherit "/std/object";
#include "/d/Terel/include/Terel.h"
#include <ss_types.h>

void
create_object()
{
   set_name("ball");
   add_name("tomas:ball");
   add_adj("wooden");
   set_short("wooden ball");
   set_long("A small wooden ball carved from a single piece of wood.\n");
   
   add_prop(OBJ_I_WEIGHT,50);
   add_prop(OBJ_I_VOLUME,50);
   add_prop(OBJ_I_VALUE,20);
   
   seteuid(getuid(TO));
}

