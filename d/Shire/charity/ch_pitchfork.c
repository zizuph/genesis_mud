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

    set_name("polearm");
    add_name(({"pitchfork"}));
    add_name("_ch_pitchfork_");
    add_adj(({"spiked"}));
    set_short("spiked pitchfork");
    set_long("This spiked pitchfork has many sharp tines and is quite " +
        "strong. It looks like it was once used to toss hay, now it's " +
        "used to defend yourself against ruffians.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_POLEARM); 
    set_dt(W_SLASH |W_IMPALE); 
    
    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);

    set_hands(W_BOTH); 
}

