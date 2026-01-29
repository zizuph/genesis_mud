/* 	gold armour for the gold knight in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("small");
    set_long("This sword is made of stone.\n");
    set_hit(10);
    set_pen(10);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 500);
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