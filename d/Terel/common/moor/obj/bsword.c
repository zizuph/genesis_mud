/*
 *   Lilith Dec 2021/Jan 2022: 
 *     -moved from Sorgum's dir
 *     -reduced set_hit to 35 since this is non-magical one handed wep
 */
inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("sword");
    set_adj("black");
    set_short("black sword");
    set_long("A black blade with a bone hilt, bearing the emblem of "+
        "a demonic face.\n");
    set_hit(35);
    set_pen(32);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
}
