/* This is file /d/Gondor/morgul/obj/stabsword.c  * 
 * A typical weapon for Morgul orcs               * 
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
  set_name(({"orcsword","sword","stabbing-sword"}));
  set_short("broad-bladed stabbing-sword");
  set_pshort("stabbing-swords");
  set_long(BSN("A broad-bladed stabbing-sword. At close quarters, a very " +
    "effective weapon. The hilt is marked by a Moon disfigured with a " +
    "ghastly face of death."));
  set_adj(({"broad-bladed", "orc"}));
  set_default_weapon(24,19,W_SWORD,W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,19)+random(250)-125);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(24, W_SWORD) + random(400) - 200));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
