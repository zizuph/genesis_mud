/* This is file /d/Gondor/morgul/obj/waraxe.c     * 
 * A waraxe for use of Ithil soldiers             * 
 * Olorin, July 1993                              * 
 * Last Modification: Olorin, July 1994
 */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon() 
{
  set_name(({"war axe","waraxe","axe","weapon"}));
  set_short("steel war axe");

  set_long(BSN("This is a war axe with a handle " +
    "made out of hard black wood. Etched into the steel " +
    "blade is the picture of a Moon disfigured with " +
    "a ghastly face of death."));
  set_adj(({"orc", "war", "steel"}));
  set_default_weapon(20,23,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,23)+random(300)-150);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(20, W_AXE) + random(500) - 250));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
