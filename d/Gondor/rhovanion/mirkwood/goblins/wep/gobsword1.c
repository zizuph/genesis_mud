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
    add_name(({"broadsword"}));
    set_short("slender broadsword");
    set_adj(({"slender"}));
    set_long("This slender broadsword is heavy, but well balanced and " +
        "extremely sharp.\n");
    	    
    set_hit(32);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1200);
    
}