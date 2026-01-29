inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"

void
create_object()
{
   set_name("jewel");
   set_adj("shining");
   set_long("This is a nice gem made by Xavier. You might want to "
           +"buy one of these for your betrothed.\n");
   add_prop(OBJ_I_VALUE, 300);
   add_name("_kalad_jewel_shop_");
add_prop(OBJ_I_VALUE,300);
}
