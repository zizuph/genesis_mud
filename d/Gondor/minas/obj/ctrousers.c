inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
  set_name("trousers");
  add_name("pair");
  add_name("pair of trousers");
  set_adj("pair");
  set_adj("of");
  set_adj("linen");
  set_adj("comfortable");
  set_adj("blue");
  set_short("pair of linen trousers");
  set_pshort("pairs of linen trousers");
  set_long(break_string(
    "A pair of comfortable blue trousers made from finest linen. \n", 75));
  set_default_armour(3,A_LEGS,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(3)+random(40));
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
