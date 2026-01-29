/*
 * Varian - 2016
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "../../defs.h"

#define ARM ({"chainmail", "chain shirt"})
#define ADJ ({"heavy", "battered", "rusty", "tattered"})
#define ADJ2 ({"steel", "iron"})

void
create_armour()
{
    string arm = one_of_list(ARM);
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2); 

    set_name(({arm}));
    add_name(({"armour"}));
    set_short(adj+" "+adj2+" "+arm);
    set_adj(({adj}));
    add_adj(({adj2}));
    set_long("This is a "+adj+" "+adj2+" "+arm+" which has seen some " +
        "better days, but it should still offer some good protection " +
        "for you in battle.\n");
    
    set_at(A_BODY);
    set_ac(30+random(10));  
}
