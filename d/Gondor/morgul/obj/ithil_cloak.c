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
  set_name("cloak");
  add_name("_ithil_armour");
  set_adj(({"sable", "black", "dark"}));
  set_short("sable cloak");
  set_pshort("sable cloaks");
  set_long(BSN(
    "This is a hooded cloak, dark like the night, made from heavy " +
    "cloth. It is the standard issue " +
    "for the armies of the Lord of Morgul. On the back is the " +
    "grey picture of the Moon disfigured with a ghastly face " +
    "of death."));
  set_default_armour(5,A_ROBE,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(200)+100);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR( 5,A_ROBE)+random(100)-50);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
