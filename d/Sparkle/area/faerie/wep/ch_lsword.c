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

    set_name("sword");
    add_name("longsword");
    add_name("_ch_longsword_");
    set_adj("sharp");
    set_adj("steel");
    set_short("sharp silver longsword"); 
    set_long("This is a " + short() + ". It is a common weapon forged by " +
        "the elves of Faerie.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

