/*
* Short sword for the guards in Gont Port
*
* Coded by Porta 971129.
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon()
{
    set_name("sword");
    add_adj(({"heavy","short-bladed"}));
    set_short("heavy short-bladed sword");
    set_pshort("heavy short-bladed swords");
    set_long("The blade of this sword is fairly thick"+
        " and made of high-quality steel. In the end is a"+
        " steel handle, wrapped with leather bands to be"+
        " more comfortable to hold. It feels heavy in your"+
        " hands.\n");
    set_hit(27);
    set_pen(29);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(27, 29) - 50 + random(100));
    add_prop(OBJ_I_WEIGHT, 6000);
}
