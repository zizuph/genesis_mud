/*  spiked club for kargs in Gont
*  Ten Alders 
*  Amelia 5/3/97
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

public void
create_weapon()
{
    set_name("club");
    set_adj(({"ebony", "spiked"}));
    set_pshort("ebony spiked clubs");
    set_short("ebony spiked club");
    set_long("A solid ebony club implanted with "+
        "needle-keen bronze spikes. An evil-looking weapon made to "+
        "crush and impale at the same time.\n");
    set_wt(W_CLUB);
    set_hit(21);
    set_pen(27);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(21, 27) + random(50));
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}
