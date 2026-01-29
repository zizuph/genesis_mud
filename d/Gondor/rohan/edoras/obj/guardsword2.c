/*
 * Rohirrim broadsword
 *
 * Last Mod: Olorin, 14-jul-1994
 * Modification log:
 * 14-jul-94 - Changed WC to broadsword according to weapon_guide
 *             added GONDOR_M_ROHIRRIM_NO_SELL prop
 */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"broadsword","sword"}));
    set_pname("broadswords");
    set_short("broadsword");
    set_pshort("broadswords");
    set_long(BSN("This is a typical Rohirrim broadsword. " +
        "It is forged of steel, and green gems are flashing on the hilt."));
    set_adj(({"steel", "broad", "rohirrim", "green-hilted"}));
    set_default_weapon(28,27,W_SWORD, W_SLASH ,W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(28, W_SWORD) + random(1000) - 500));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,27) + random(800) - 400);
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
