inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
  set_name("cloak");
  set_adj("flowing");
  set_adj("black");
  set_pshort("flowing black cloaks");
   set_long("A heavy black cloak, with a swirling design " +
    "woven into the woolen fabric. \n");
  set_default_armour(5,A_ROBE,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(60));
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
