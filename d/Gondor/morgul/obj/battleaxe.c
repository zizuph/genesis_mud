/* This is file /d/Gondor/morgul/obj/battleaxe.c     * 
 * A battleaxe for use of Ithil soldiers             * 
 * Olorin, July 1993                                 * 
 * Modified, Olorin, July 1994                       */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon() 
{
  set_name(({"battle axe","battleaxe","axe","weapon"}));
  set_short("steel battle axe");

  set_long(BSN("This is a large heavy battle axe with a handle " +
    "made out of hard black wood. Etched into the steel " +
    "blade is the picture of a Moon disfigured with " +
    "a ghastly face of death."));
  set_adj(({"orc", "large", "heavy", "battle", "steel"}));
  set_default_weapon(24,30,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,30)+random(300)-150);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(24, W_AXE) + random(400) + 400));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}

