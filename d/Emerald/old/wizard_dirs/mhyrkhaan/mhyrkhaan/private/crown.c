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
   set_name("crown");
   set_adj("power");
   add_adj("unearthly");
    set_short("Crown of Unearthly Power");
   set_long("A large crystaline crown glowing with power.\n");
   set_at(A_HEAD);
   set_ac(10);
   add_prop(OBJ_I_WEIGHT,70);
   add_prop(OBJ_I_VOLUME,70);
   add_prop(OBJ_I_VALUE,70);
}
