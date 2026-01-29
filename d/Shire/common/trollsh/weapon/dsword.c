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

#define WEP ({"sword", "claymore", "longsword"})
#define ADJ ({"battered", "ugly", "sharp", "rusty", "jagged"})
#define ADJ2 ({"double-edged", "notched", "deadly", "steel", "iron"})

void
create_weapon()
{

    string wep = one_of_list(WEP);
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2);   

    set_name(({wep}));
    add_name(({"sword"}));
    set_short(adj+" "+adj2+" "+wep);
    set_adj(({adj}));
    add_adj(({adj2}));
    set_long("This is a "+adj+" "+adj2+" "+wep+" which seems to have been " +
        "poorly maintained. However, it still looks like it could be a " +
        "very useful weapon in battle.\n");
    	    
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    set_hit(35+random(5));
    set_pen(35+random(5));
}