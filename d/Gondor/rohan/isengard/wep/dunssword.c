inherit "/std/weapon";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

/* dunlending short sword for use around Isengard in the domain Gondor of         
* Genesis by Xeros of GondorMud 19 Dec 1993. */

void
create_weapon()
{
    set_name("sword");
    set_short("sharp shortsword");
    set_adj("sharp");
    add_name("shortsword");
    set_long(BSN("A shortsword commonly issued to scouts and other secondary "+
        "fighters. It bears the symbol of the forges of Saruman."));
    set_default_weapon(37,28,W_SWORD,W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(37, W_SWORD));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(37, 28));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
