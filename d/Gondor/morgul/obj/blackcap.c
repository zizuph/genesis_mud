inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
  set_name("cap");
  add_name(({"helmet","ringmail helmet"}));
  add_name("_ithil_armour");
  set_short("black cap");
  set_pshort("black caps");
  set_adj(({"black", "ringmail", "leather"}));
  set_long(BSN(
    "The black cap has an iron rim, and iron hoops covered with leather " +
    "upon which the picture of a Moon disfigured with a ghastly face of " +
    "death is painted above the beaklike nose-guard."));
  set_default_armour(15,A_HEAD,({-2, 3,-1}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(15)+random(50)-25);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(15,A_HEAD)+random(200)-100);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }

