inherit "/std/receptacle";
#include "/d/Kalad/defs.h".
#include "/sys/stdproperties.h"
int turns;
/* by korat */
void
create_receptacle()
{
   set_name("cylinder");
   set_adj("metal");
   set_long("A small metal cylinder with a small lid on the top. "+
      "Its usually used to carry messages by attaching it to a pigeons leg.\n");
   add_prop(CONT_I_WEIGHT, 10);
   add_prop(CONT_I_MAX_WEIGHT, 200);
   add_prop(CONT_I_VOLUME, 100);
   add_prop(CONT_I_MAX_VOLUME, 210);
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_M_NO_SELL,1);
}

