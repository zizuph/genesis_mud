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

#define ARM ({"shield"})
#define ADJ ({"wooden", "painted", "sturdy", "strong", "light", "wide"})
#define ADJ2 ({"round", "oval", "long"})

void
create_armour()
{
    string arm = one_of_list(ARM);
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2); 

    set_name(({arm}));
    add_name(({"armour"}));
    add_name(({"shield"}));
    set_short(adj+" "+adj2+" "+arm);
    set_adj(({adj}));
    add_adj(({adj2}));
    set_long("This is a "+adj+" "+adj2+" "+arm+" which looks like it " +
        "should be very useful in battle.\n");
    
    set_at(A_SHIELD);
    set_ac(30+random(10));  
}
