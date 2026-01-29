inherit "/std/object.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("diamond");
   set_adj("sparkling");
   add_adj("white");
   set_short("sparkling white diamond");
   set_pshort("sparkling white diamonds");
   set_long("Sparkling with a strange white light of its own, its radiant "+
      "crystal beauty leaves you gasping with wonderment.\n");
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
