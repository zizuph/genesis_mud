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
    set_short("black iron longsword");
    set_adj(({"black", "iron"}));
    set_long("Crafted from a black iron, this sword has a sinister and " +
        "deadly appearance. The blade is slightly notched from hard use, " +
        "but you feel it would still be an effective weapon in your " +
        "hands.\n");
    	    
    set_hit(31);
    set_pen(31);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 1700);
    add_prop(OBJ_I_VOLUME, 1200);
    
}