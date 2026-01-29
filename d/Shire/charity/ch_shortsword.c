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

    set_name("shortsword");
    set_name("sword");
    add_name("_ch_shortsword_");
    set_pname("shortswords");
    set_pname("swords");
    set_short("shiny shortsword");
    set_pshort("shiny shortswords");
    set_adj("shiny");
    set_long("The " + short() + " is made from polished steel. It fits neatly " +
        "in your hand and could probably inflict some damage.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

