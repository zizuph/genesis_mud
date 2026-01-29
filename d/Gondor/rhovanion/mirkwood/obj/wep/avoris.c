/*
 * Based on Eowul's code for graded weapons as are found and
 * designed for Mirkwood.
 * 
 * Varian 2015
 */

#pragma strict_types

#include "../../defs.h"

inherit MIRKWOOD_OBJ_DIR + "wep/magical_weapon";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

void
create_magical_weapon() 
{
    set_name(({"avoris"}));
    add_name(({"cutlass", "sword"}));
    set_short("black steel cutlass");
    set_adj(({"black", "steel"}));
    set_long("This cutlass is made of a steel so dark it looks almost black. " +
        "The sword itself is not only incredibly sharp, it is so well " +
        "balanced that it feels as light as a feather in your hands.\n");
            
    set_hit(33);
    set_pen(33);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);

    // TODO set properties such as weight, value and magical information

    setuid();
    seteuid(getuid());

    object effect = clone_object(MIRKWOOD_OBJ_DIR + "effects/stat_bonus_str");
    effect->set_average_range(50, 70);
    effect->set_level(2);
    
    set_effect(effect);
}

