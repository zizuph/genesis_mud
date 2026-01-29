/* Shield of the Morgul armies */
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
  set_name("shield");
  set_short("black steel shield");
  set_pshort("steel shields");
  set_adj(({"morgul", "black", "steel","round"}));
  set_long(BSN("This is a round shield of steel, forged " +
    "in the pits below Barad-dur for the armies of the Lord of Morgul. " +
    "In the center the shield shows as coat of arms the picture of " +
    "the Moon disfigured with a ghastly face of death on a field of " +
    "black."));
  set_default_armour(25,A_SHIELD,({0,0,0}),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(500)-250);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_SHIELD)+random(1000)-500);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }

