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

#define ARM ({"greaves"})
#define ADJ ({"scratched", "battered", "rusty", "dented"})
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
    set_long("These "+adj+" "+adj2+" "+arm+" have seen some " +
        "better days, but it should still offer some good protection " +
        "for your legs.\n");
    
    set_at(A_LEGS);
    set_ac(30+random(10));  
}
