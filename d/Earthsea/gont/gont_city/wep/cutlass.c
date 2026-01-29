/* cutlass wielded by seamen in Gont Port
*
*  Amelia 3/8/98
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

public void
create_weapon()
{
    set_name("cutlass");
    add_name("sword");
    set_adj(({"blue","steel"}));
    set_short("blue steel cutlass");
    set_pshort("blue steel cutlasses");
    set_long("This is a blue steel "+
        "cutlass, which is shiny and has a keen edge.\n");
    set_wt(W_SWORD);
    set_hit(30);
    set_pen(30);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 30) + random(10));
}

string
query_recover()
{
    return MASTER + ":"+query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}
