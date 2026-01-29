/*spear.c
*Standard spear in the elvish armies
*By Mhyrkhaan, November 1998.
*/
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
void
create_weapon()
{
    set_name("spear");
    add_name("steel");
    set_short("sharp steel spear");
    add_adj( ({"sharp" , "steel"}) );
    set_long("This sharp steel spear is about the length of a man. It has a " +
        "double edged wide blade on the end of it that is about 12 inches long.\n");
    set_hit(23);
    set_pen(17);
    set_pm(({ 3, 2, 0 }));
    add_prop(OBJ_I_WEIGHT, 1300); 
    add_prop(OBJ_I_VOLUME,  550);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_BOTH);
}
