/*
 * Rohirrim shortsword
 * Last mod: Olorin, 14-jul-1994
 * Modification log: 
 * 14-jul-94: Changed WC to follow new weapon_guide,
 *            changed into shortsword,
 *            added GONDOR_M_ROHIRRIM_NO_SELL prop
 *            Olorin
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
    set_name(({"shortsword","sword"}));
    set_short("shortsword");
    set_pshort("shortswords");
    set_adj(({"short", "rohirrim", "steel", "green-hilted"}));
    set_long(BSN("This is a typical Rohirrim shortsword. It is " +
        "forged of steel, and green stones are flashing on the hilt."));
    set_default_weapon(22, 18, W_SWORD, W_IMPALE, W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(22, W_SWORD) + random(400) - 200));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22, 18) + random(300));
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
