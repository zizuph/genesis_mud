/*
* Knife for the citizens in Gont Port
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
    set_name("dagger");
    add_adj(({"short","steel"}));
    set_short("short steel dagger");
    set_pshort("short steel daggers");
    set_long("A short dagger made from steel, polished"+
        " until it shines. The oakwood hilt is smooth"+
        " from years of use and ends in a knob of steel."+
        " Looking at the short blade ending in a sharp"+
        " tip, you think this might be a decent stabbing"+
        " weapon.\n");
    set_hit(12);
    set_pen(15);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15, 12) - 20 + random(40));
}
