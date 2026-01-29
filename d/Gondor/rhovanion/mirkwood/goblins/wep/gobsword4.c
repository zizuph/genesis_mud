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
    add_name(({"shortsword"}));
    set_short("sharp iron shortsword");
    set_adj(({"sharp", "iron"}));
    set_long("This shortsword is plainly made, but with a sharp point " +
        "that looks like it should be quite effective in combat.\n");
    	    
    set_hit(33);
    set_pen(30);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 1600);
    add_prop(OBJ_I_VOLUME, 1200);
    
}