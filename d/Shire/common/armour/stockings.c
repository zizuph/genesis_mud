inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
   set_ac(2);
   set_at(A_LEGS);
   set_name("stockings");
   set_short("pair of silk stockings");
   set_long(break_string("These silk stockings will give you some "
   + "protection.\n",50));
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
