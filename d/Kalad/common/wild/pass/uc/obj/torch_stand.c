inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("stand");
   set_adj("torch");
   set_long("A five foot high stand, a torch is currently set within its holder, "+
      "providing a steady and bright light.\n");
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
   add_prop(OBJ_I_LIGHT,1);
   add_prop(OBJ_M_NO_GET,"It is firmly bolted to the ground!\n");
}
