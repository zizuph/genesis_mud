inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
string
   query_auto_load()
{
return MASTER;
}
void
create_armour()
{
::create_armour();
   set_name("apron");
   set_adj("stained");
   add_adj("old");
   set_short("old stained apron");
   set_long("a dirty old apron, it has many stains on it.\n");
   set_at(A_TORSO);
   set_ac(2);
   add_prop(OBJ_I_WEIGHT,700);
   add_prop(OBJ_I_VOLUME,700);
   add_prop(OBJ_I_VALUE,700);
}
