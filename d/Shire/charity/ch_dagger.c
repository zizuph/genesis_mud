/*
 * Charity box weapon
 * by Finwe, April 2005
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 10 + random (5),
    pen = 10 + random (5);
void
create_weapon()
{

    set_name("knife");
    add_name("dagger");
    add_name("_ch_dagger_");
    set_adj("slim");
    set_adj("steel");
    set_short("slim steel dagger"); 
    set_long("This is a " + short() + ". It is slim and deadly looking. " +
        "The dagger was forged by a skilled smith. It looks small enough " +
        "to be hidden on your body.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 
    
    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);

    set_hands(W_ANYH); 
}

