inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_object()
{
   set_name("plate");
   add_name("_shire_pieplate_");
   add_adj(({"silver","pie"}));
   set_short("silver pie plate");
   set_long("This silver pie plate looks well used, "+
   "and smells of bumbleberries!\n");

   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 400);

}
