/*
* Axe for the guards in Gont Port
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
    set_name(({"waraxe","axe"}));
    add_adj(({"short-hafted","steel"}));
    set_short("short-hafted steel waraxe");
    set_pshort("short-hafted steel waraxes");
    set_long("This axe looks like a dangerous weapon,"+
        " made completely of heavy steel with"+
        " a sharp blade crowning"+
        " the top. The opposite side of the blade is a"+
        " blunt hammer head. The end of the short handle"+
        " is wrapped with a leather band to make the"+
        " grip more secure.\n");
    set_hit(29);
    set_pen(28);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29, 28) - 50 + random(100));
    add_prop(OBJ_I_WEIGHT, 7000);
}
