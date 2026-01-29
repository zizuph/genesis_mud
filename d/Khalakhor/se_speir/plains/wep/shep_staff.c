inherit "/d/Khalakhor/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_khalakhor_weapon()
{
    set_name("staff");
    add_name("polearm");
    set_adj("wooden");
    add_adj("shepherds");
    set_short("wooden shepherds staff");
    set_long("A wooden shepherds staff, made of a long rough tree limb.\n");
 
    set_hit(10);
    set_hands(W_BOTH);
    set_pen(10);
 
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
}
