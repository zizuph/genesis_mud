inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"sheperds staff","staff"}));
    set_adj("wood");
    set_short("shepherds staff");
    set_long("A wooden sheperds staff, made of a long rough tree limb.\n");
 
    set_hit(10);
    set_hands(W_BOTH);
    set_pen(10);
 
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
}
