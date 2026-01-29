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
    set_adj(({"long", "steel"}));
    set_short("long steel dagger");
    set_long("This is a long steel dagger, with a sharp curved " +
        "edge. Somewhat smaller than a short sword, it is stiletto " +
        "thin and has a blackened ivory hilt.\n");
    set_hit(12);
    set_pen(16);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_LEFT);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12, 16) - 20 + random(40));
    add_prop(OBJ_I_VOLUME, 500);
}
