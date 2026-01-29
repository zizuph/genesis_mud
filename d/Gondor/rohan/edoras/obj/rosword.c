/* The typical sword of the Rohirrim */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"sword","weapon","longsword"}));
    set_pname("swords");
    add_pname("longswords");
    set_short("rohirrim longsword");
    set_pshort("rohirrim longswords");
    set_adj(({"rohirrim", "long", "bright", "green-hilted"}));
    set_long(BSN("The sword is long and bright, and there " +
        "are green gems set in the hilt. This is the typical " +
        "sword of the Men of Rohan."));
    set_default_weapon(29,25,W_SWORD,W_SLASH|W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(29, W_SWORD) + random(1000) - 500));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29,25)-250+random(500));
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
