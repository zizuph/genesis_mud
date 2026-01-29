/*
 * Varian - 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "../guild.h"

#define ARM ({"hat"})
#define ADJ ({"small"})
#define ADJ2 ({"black"})

void
create_armour()
{
    string arm = one_of_list(ARM);
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2); 

    set_name(({arm}));
    add_name(({"armour"}));
    add_name(({"hat"}));
    set_short("small black hat");
    set_adj(({adj}));
    add_adj(({adj2}));
    set_long("This is a "+adj+" "+adj2+" "+arm+" which belongs to " +
        "the scribe of Angmar's Army\n");
    
    set_at(A_HEAD);
    set_ac(8+random(4)); 
}
