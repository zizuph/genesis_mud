/* Sword of the Dephonian Priests */
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name("sword");
    set_adj("dephonian");
    set_short("dephonian sword");
    set_long("A steel sword engraved with a raven on the hilt.\n");
 
    set_hit(20);
    set_pen(20);
 
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1500);
}
