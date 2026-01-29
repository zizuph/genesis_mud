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
   set_name("cloak");
   set_adj("black");
   add_adj("rune-covered");
   set_short("rune-covered black cloak");
   set_long("a black cloak, with glowing silver runes all over it.\n");
   set_at(A_TORSO);
   set_ac(10);
   add_prop(OBJ_I_WEIGHT,700);
   add_prop(OBJ_I_VOLUME,700);
   add_prop(OBJ_I_VALUE,700);
}
