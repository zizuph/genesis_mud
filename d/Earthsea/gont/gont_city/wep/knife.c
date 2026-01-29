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
    set_name("knife");
    set_pname("knives");
    set_short("sharp curved knife");
    set_pshort("sharp curved knives");
    set_adj(({"sharp", "curved"}));
    set_long("This is a"+
        " sharp curved knife with a bone hilt. There"+
        " is a small figure of a skull carved into the hilt.\n");
    set_hit(15);
    set_pen(12);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15, 12) - 20 + random(40));
    add_prop(OBJ_I_WEIGHT, 2500);
}
