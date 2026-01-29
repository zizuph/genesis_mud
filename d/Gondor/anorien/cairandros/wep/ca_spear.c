/*
 * Spear for soldiers inhabiting the basement in Cair Andros
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
    set_name("spear");
    set_short("long steel spear");
    set_adj("long");
    add_adj("steel");
    set_long("This spear is about five feet long and boasts " +
        "a sharp steel point at the end. This spear would " +
        "clearly be deadly in the hands of a trained warrior. " +
        "The seven stars and white tree of Gondor have been " +
        "etched on the shaft of the spear.\n");
    	    
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    set_hit(32);
    set_pen(32);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}