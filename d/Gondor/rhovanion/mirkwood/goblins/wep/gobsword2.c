/*
 * Varian - February 5 2016
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <wa_types.h>

void
create_weapon()
{
    int rand;
    
    set_name(({"sword"}));
    add_name(({"longsword"}));
    set_short("tempered steel longsword");
    set_adj(({"tempered", "steel"}));
    set_long("This longsword has been finely crafted from tempered steel. " +
        "The double-edged blade is sharp and has obviously been kept in " +
        "good condition.\n");
    	    
    set_hit(30);
    set_pen(36);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1200);
    
}