inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
  set_name("tunic");
  set_adj("muslin");
  set_adj("embroidered");
set_short("embroidered muslin tunic");
  set_pshort("embroidered muslin tunics");
   set_long("A muslin tunic, worn by the working people, both " +
   "men and women. The tunic is loose enough to be comfortable, " +
   "and plain enough for working in a variety of " +
   "environments. The hem and collar are embroidered with an ivy motif.\n");
  set_default_armour(5,A_ROBE,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(40));
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
