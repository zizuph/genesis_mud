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
    add_name("club");
    add_name("_ch_club_");
    set_adj("heavy");
    set_adj("spiked");
    set_short("heavy spiked club"); 
    set_long("This is a " + short() + ". Made by trolls, it is a spiked " +
        "ball sitting on top of a long pole. The weapon looks fearsome " +
        "and could probably damage a foe in battle.\n");
    
    set_hit(hit);
    set_pen(pen);
    set_wt(W_CLUB);
    set_dt(W_IMPALE | W_BLUDGEON);
    
    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1000);

    set_hands(W_ANYH); 
}

