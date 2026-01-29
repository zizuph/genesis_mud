/* Hammer found in the forge of the Temple of Dephonia */
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"forge hammer","hammer"}));
    set_adj("iron");
    set_short("forge hammer");
    set_long("A thick iron hammer used to shape metal.\n");
 
    set_hit(20);
    set_hands(W_NONE);
    set_pen(20);
 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
}
