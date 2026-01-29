#include "defs.h"
inherit "/std/object";

void
create_object()
{
   set_name(({"glue","bottle"}));
   set_adj("glue");
   set_short("bottle of glue");
   set_pshort("bottles of glue");
   set_long("This is a plain bottle of white glue.\n");

   add_prop(OBJ_I_WEIGHT, 150);
   add_prop(OBJ_I_VOLUME, 240);
   add_prop(OBJ_I_VALUE, SILVER_VALUE);
}
