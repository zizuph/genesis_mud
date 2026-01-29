/* The Nazgul's Black Robes */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_armour() {
  set_name("robes");
  add_name("robe");
  set_adj("black");
  set_adj("hooded");
  set_short("black hooded robe");
  set_long("This is a large black robe, with a wide hood.\n");
  set_ac(2);
  set_at(A_ROBE);
  set_am(({0,0,0}));
  add_prop(OBJ_I_WEIGHT,400);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(2)+random(100)-100);
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
