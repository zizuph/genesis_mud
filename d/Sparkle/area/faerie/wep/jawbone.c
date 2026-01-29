/*
 * Charity box weapon
 * by Finwe, April 2005
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 10 + random (5)+1,
    pen = 10 + random (5)+1;
void
create_weapon()
{

    set_name("club");
    add_name("jawbone");
    add_name("_orc_jawbone_");
    set_adj("heavy");
    set_short("heavy jawbone"); 
    set_long("This is a " + short() + ". It is long and 'L' shaped. On the inside the teeth are still attached to the jawbone. Even though it is bone, the club looks magically enhanced to deliver deadly blows to enemies.\n");
    
    set_hit(hit);
    set_pen(pen);
    set_wt(W_CLUB);
    set_dt(W_IMPALE | W_BLUDGEON);
    
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1000);

    set_hands(W_ANYH); 
}

