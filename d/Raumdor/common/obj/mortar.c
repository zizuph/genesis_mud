#include "defs.h"
inherit "/std/container";

void
create_container()
{
   set_name(({"mortar","bucket","_mortar_bucket"}));
   set_adj("mortar");
   set_short("bucket of mortar");
   set_pshort("buckets of mortar");
   set_long("This is a large bucket of grey mortar.\n");

   add_prop(CONT_I_HIDDEN, 1);
   add_prop(CONT_I_RIGID, 1);
   add_prop(CONT_M_NO_INS, 1);
   add_prop(CONT_M_NO_REM, 1);
   add_prop(CONT_I_WEIGHT, 150);
   add_prop(CONT_I_VOLUME, 240);
   add_prop(OBJ_I_VALUE, COPPER_VALUE * 3);
}
