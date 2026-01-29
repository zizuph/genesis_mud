/* This is file /d/Gondor/morgul/obj/spear.c      * 
 * A glaive                                        * 
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
  set_name(({"lance","glaive","polearm","weapon"}));
  set_short("long glaive");
  set_pshort("long glaives");
  set_long(BSN("A glaive with a sharp pointed steel blade. The shaft is made " +
    "from a hard black wood, and the places where it is held in combat are " +
    "covered with leather. Below the blade the shaft shows the picture of " +
    "a Moon disfigured with a ghastly face of death."));
  set_adj(({"long", "sharp", "pointed"}));
  set_default_weapon(23,30,W_POLEARM,W_IMPALE,W_BOTH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(23,30)+random(500)-100);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(23, W_POLEARM) + random(1000) - 500));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
