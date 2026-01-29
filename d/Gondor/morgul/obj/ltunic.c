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
  set_name("tunic");
  add_name("_ithil_armour");
  set_adj(({"leather", "thick", "dirty"}));
  set_short("thick leather tunic");
  set_pshort("thick leather tunics");
  set_long(BSN(
    "A thick tunic of dirty leather. On the left shoulder is a " +
    "black brand showing a Moon disfigured with a ghastly face " +
    "of death."));
  set_default_armour(8,A_ROBE,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(8)+random(100)-50);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR( 8,A_ROBE)+random(100)-50);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }

