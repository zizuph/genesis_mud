/*
 * Sword for soldiers inhabiting the basement in Cair Andros
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
    set_name("broadsword");
    add_name("sword");
    set_short("deadly steel broadsword");
    set_adj("deadly");
    add_adj("steel");
    set_long("This broadsword has been forged from the finest " +
        "steel, and it holds an incredibly sharp edge. It " +
        "looks like it would be deadly in the hands of a " +
        "trained warrior. The seven stars and white tree of " +
        "Gondor have been etched on the blade.\n");
    	    
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    set_hit(35);
    set_pen(35);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}