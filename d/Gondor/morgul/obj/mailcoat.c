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
  set_name("coat");
  add_name("ringmail");
  add_name("_ithil_armour");
  set_adj(({"stout", "plated"}));
  set_short("coat of ringmail");
  set_pshort("coats of ringmail");
  set_long(BSN(
    "A stout coat of ringmail with a steel breastplate on which " +
    "a Moon disfigured with a ghastly face of death has been " +
    "painted."));
  set_default_armour(21,A_BODY,({-1,2,-1}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(21)+random(200)-100);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(21,A_BODY)+random(400)-200);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
