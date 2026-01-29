
inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()

{
   set_ac(10);
   set_at(A_ROBE);
   set_name(({"small white dress","small dress","white dress","dress"}));
   set_long(break_string("This seemed to have been made for "
   + "a princess. The materials are unknown too you but look "
   + "quite strong.\n",50));
}


query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
