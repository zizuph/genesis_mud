/*
 * Axe for soldiers inhabiting the basement in Cair Andros
 *
 * Varian - February, 2020
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "../../defs.h"

void
create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_short("sharp steel battleaxe");
    set_adj("sharp");
    add_adj("steel");
    set_long("This battleaxe has been forged from the finest " +
        "steel, and it holds an incredibly sharp edge. It " +
        "looks like it would be deadly in the hands of a " +
        "trained warrior. The seven stars and white tree of " +
        "Gondor have been etched on the haft.\n");
    	    
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    set_hit(32);
    set_pen(32);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}