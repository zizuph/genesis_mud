/*cleaver.c
*Cook's weapon in the evlen outpost
*By Mhyrkhaan, November 1998.
*/
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
void
create_weapon()
{
    set_name("cleaver");
    add_name("butcher's");
    set_short("heavy butcher's cleaver");
    add_adj( ({"heavy"}) );
    set_long("This heavy butcher's cleaver looks like it can cut through " +
        "flesh and bone with relative ease.\n");
    set_hit(14);
    set_pen(20);
    set_pm(({ -2, 1, 0 }));
    add_prop(OBJ_I_WEIGHT, 1300); 
    add_prop(OBJ_I_VOLUME,  350);
    set_wt(W_AXE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
