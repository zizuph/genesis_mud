inherit "/std/object.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("feather");
   set_adj("long");
   add_adj("thin");
   set_long("An incredibly long and thin feather, otherwise there is "+
      "nothing of note about it.\n");
   add_prop(OBJ_M_NO_SELL,"This feather is worthless! Noone will buy this!\n");
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_LIGHT,1);
}
