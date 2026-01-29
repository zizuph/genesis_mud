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
    set_short("shiny steel shortsword");
    set_adj(({"shiny", "steel"}));
    set_long("This sword has a deadly looking point and appears to have " +
        "been crafted from the finest steel. It is also well balanced, " +
        "feeling incredibly comfortable in your hand.\n");
    	    
    set_hit(36);
    set_pen(32);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1200);
    
}