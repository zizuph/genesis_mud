/*
 * Varian - 2016
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "../../defs.h"

#define WEP ({"club"})
#define ADJ ({"heavy", "massive", "large", "huge"})
#define ADJ2 ({"spiked", "wooden", "banded"})

void
create_weapon()
{

    string wep = one_of_list(WEP);
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2);   

    set_name(({wep}));
    add_name(({"club"}));
    set_short(adj+" "+adj2+" "+wep);
    set_adj(({adj}));
    add_adj(({adj2}));
    set_long("The "+adj+" "+adj2+" "+wep+" is extremely heavy, yet" +
        "poorly maintained. However, it still looks like it could be a " +
        "very useful weapon in battle.\n");
    	    
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(35+random(5));
    set_pen(35+random(5));
}