inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("oar");
    add_adj("rowing");
    set_short("rowing oar");
    set_long("It is a finely crafted oar.\n");

    set_hit(8);
    set_pen(12);
    
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, 10);
}
