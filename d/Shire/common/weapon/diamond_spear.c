


inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name(({"spear","diamond-tipped spear"}));
    set_adj("diamond-tipped");
    set_hit(30);
    set_pen(35);
    set_wt(W_JAVELIN);
    set_hands(W_BOTH);
    set_dt(W_IMPALE);
    set_long("A diamond-tipped spear.\n");
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, 2000);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}



