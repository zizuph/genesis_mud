inherit "/std/leftover";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_leftover()
{
   set_name("pelt");
   set_adj("fine");
   add_adj("lion");
   set_long("A finely matted pelt, no doubt once belonging to a lion.\n");
   set_decay_time(100);
   set_amount(250);
   add_prop(OBJ_I_VALUE,100);
}
