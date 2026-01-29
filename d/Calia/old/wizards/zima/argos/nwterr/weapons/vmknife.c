inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"pruning knife","knife"}));
    set_adj("steel");
    set_short("pruning knife");
    set_pshort("pruning knives");
    set_long("A short steel knife used to prune grapevines.\n");
 
    set_hit(10);
    set_hands(W_NONE);
    set_pen(10);
 
    set_wt(W_KNIFE);
    set_dt(W_SLASH);
 
    add_prop(OBJ_I_WEIGHT,  900);
    add_prop(OBJ_I_VOLUME,  900);
}
