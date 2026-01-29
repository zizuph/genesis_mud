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
  set_name("chainmail");
  add_name(({"mail", "coat"}));
  add_name("_ithil_armour");
  set_adj(({"chain", "steel", "black", "plated"}));
  set_short("black chainmail");
  set_pshort("black chainmails");
  set_long(BSN(
    "A black coat of chainmail with a steel breastplate on which " +
    "a Moon disfigured with a ghastly face of death has been " +
    "painted."));
  set_default_armour(29,A_BODY,({-2,3,-1}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(29)+random(600)-200);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR( 29, A_BODY)+random(500)-250);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
