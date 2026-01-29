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

    set_name("spear");
    add_name("polearm");
    add_name("_ch_spear_");
    set_adj("small");
    set_adj("wooden");
    set_short("small wooden spear"); 
    set_long("This small wooden spear is normally used for hunting small " +
        "animals that live in the Shire. It doesn't look like much but " +
        "can skewer a rabbit or a mouse easily.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_POLEARM); 
    set_dt(W_IMPALE); 
    
    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);

    set_hands(W_LEFT); 
}

