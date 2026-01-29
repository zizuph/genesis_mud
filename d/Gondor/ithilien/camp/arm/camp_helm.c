inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour() 
{
  set_name("helm");
  add_name(({"helmet","plate helmet"}));
  set_short("camouflaged helm");
  set_pshort("camouflaged helms");
  set_adj(({"camouflaged", "plate"}));
  set_long("This plate helmet resembles those crafted in the smithies "
    + "of Gondor. It has been painted in such a way to make it less obvious "
    + "in a forest setting.\n");
  set_default_armour(25,A_HEAD,({0,0,0}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(1500)-500);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_HEAD)+random(1000)-500);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(GONDOR_M_RANGERS_NO_SELL,1);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}

query_recover()  { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
