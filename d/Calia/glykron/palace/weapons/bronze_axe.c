/* 	bronze axe for the bronze knight in the crystalline palace

    coder(s):   Glykron

    history:     9. 2.92    header added                    Glykron
                 9. 2.92    last modified                   Glykron

*/

#pragma save_binary

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("bronze");
    set_short("bronze axe");
    set_long("This bronze axe is of a dwarven make.\n");
    set_hit(25);
    set_pen(25);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 5000);
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