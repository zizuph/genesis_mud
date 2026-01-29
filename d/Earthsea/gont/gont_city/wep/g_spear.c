/*
* Spear for the guards in Gont Port
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
    set_name("spear");
    add_adj(({"long", "ash-hafted"}));
    set_short("long ash-hafted spear");
    set_pshort("long ash-hafted spears");
    set_long("This is a long spear, about two meters in"+
        " length with a"+
        " shaft of strong ash wood, whittled and polished"+
        " carefully to a round and smooth shape, comfortable"+
        " to hold on to. It is crowned by a sharp steel"+
        " tip.\n");
    set_hit(25);
    set_pen(35);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25, 35) - 50 + random(100));
    add_prop(OBJ_I_WEIGHT, 9000);
}
