inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"timber axe","axe"}));
    set_adj("steel");
    add_adj("common");
    set_short("common timber axe");
    set_long("A steel axe with a long handle, used to down trees.\n");
 
    set_hit(10);
    set_hands(W_NONE);
    set_pen(10);
 
    set_wt(W_AXE);
    set_dt(W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}
