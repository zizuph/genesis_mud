/* 	this is a weapon of the young knight in the crystalline palace

    coder(s):   Glykron

    history:     5. 5.92    header and recovery added       Glykron

    purpose:    weapon
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("iron");
    set_short("iron sword");
    set_long("This sword is made of iron.\n");
    set_hit(20);
    set_pen(20);
    set_hands(W_RIGHT);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
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