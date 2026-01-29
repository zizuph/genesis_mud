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
    set_name("scramasax");
    add_name("sword");
    set_adj(({"rusty", "iron"}));
    set_pname("scramasaxes");
    set_short("rusty iron scramasax");
    set_pshort("rusty iron scramasaxes");
    set_long("This is an old scramasax, which is a light "+
        "shortsword with a single razor-sharp edge. It is used mostly "+
        "for slashing.\n");
    set_hit(18);
    set_pen(19);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 19));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
