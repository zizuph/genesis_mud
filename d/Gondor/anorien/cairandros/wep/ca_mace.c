/*
 * Mace for soldiers inhabiting the basement in Cair Andros
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
    set_name("mace");
    add_name("club");
    set_short("heavy steel mace");
    set_adj("heavy");
    add_adj("steel");
    set_long("The head of this mace has been forged from " +
        "the finest steel and it looks like it would be " +
        "a lethal weapon in the hands of a trained warrior. " +
        "The seven stars and white tree of Gondor have " +
        "been etched on the haft.\n");
    	    
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(32);
    set_pen(32);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}