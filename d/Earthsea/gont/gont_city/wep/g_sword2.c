/*
* Long sword for the guards in Gont Port
*
* Coded by Porta 971129.
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("sword");
    add_adj(({"long","broad-bladed"}));
    set_short("long broad-bladed sword");
    set_pshort("long broad-bladed swords");
    set_long("This sword has a long, fairly broad"+
        " blade of sharpened quality"+
        " steel attached to a wooden handle wrapped with"+
        " leather to make it comfortable to hold."+
        " The length of the blade together with the weight"+
        " of the massive steel makes you think you could"+
        " deal powerful swings with this weapon.\n");
    set_hit(26);
    set_pen(33);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VALUE, 828+random(100));
    add_prop(OBJ_I_WEIGHT, 8000);
}
