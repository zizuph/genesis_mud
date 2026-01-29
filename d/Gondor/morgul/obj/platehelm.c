/*
 * Last Modification: Olorin, July 1994
 */
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
  add_name("_ithil_armour");
  set_short("tabarded helm");
  set_pshort("tabarded helms");
  set_adj(({"black", "plate", "tabarded"}));
  set_long(
    "This is a tabarded helmet of black steel, forged in the pits below " +
    "Barad-dur for the officers of the armies of the Dark Lord. Above the " +
    "nose guard, a picture is etched into the steel, showing a Moon " +
    "disfigured with a ghastly face of death.\n");
  set_default_armour(25,A_HEAD,({-1,0,1}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(1500)-500);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_HEAD)+random(1000)-500);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
