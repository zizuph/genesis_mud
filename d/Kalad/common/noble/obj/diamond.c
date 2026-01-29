inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"

void
create_object()
{
   set_name("diamond");
   set_adj("shining");
   set_long("This is a beautiful small diamond gem cut to perfection. "+
   "It gleams brightly.\n");
   add_prop(OBJ_I_VALUE, 5000);
   add_name("_kalad_jewel_shop_");
   add_prop(OBJ_I_VALUE,300);
}
