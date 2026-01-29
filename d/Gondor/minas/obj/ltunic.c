inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
  set_name("tunic");
  set_adj("leather");
  set_adj("light");
  set_short("light leather tunic");
  set_pshort("light leather tunics");
  set_long(break_string(
    "A light leather tunic made of tanned doeskin, decorated with embroidery. \n", 75));
  set_default_armour(5,A_ROBE,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(40));
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
