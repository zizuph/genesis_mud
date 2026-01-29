/*
* Club for the fishermen in Gont Port
*
* Coded by Porta 971130.
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon()
{
    set_name(({"stick","club"}));
    add_adj(({"sturdy","wooden"}));
    set_short("sturdy wooden stick");
    set_pshort("sturdy wooden sticks");
    set_long("This is a sturdy wooden stick, about"+
        " one half meter long and smooth from years of"+
        " usage. There are stains of blood on one edge,"+
        " and traces of fish scales.\n");
    set_hit(13);
    set_pen(16);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_LEFT);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(13, 16) - 20);
    add_prop(OBJ_I_WEIGHT, 7000);
}
