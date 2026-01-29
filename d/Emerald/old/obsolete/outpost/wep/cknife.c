/*cknife.c
*Cook's weapon in the elven outpost
*By Mhyrkhaan, November 1998.
*/
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
void
create_weapon()
{
    set_name("knife");
    add_name("cooking");
    set_short("large cooking knife");
    add_adj( ({"large"}) );
    set_long("This long knife is sharp and lightwight for use in the kitchen.\n");
    set_hit(10);
    set_pen(12);
    set_pm(({ 0, 1, 0 }));
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME,  250);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
