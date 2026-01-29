#pragma save_binary

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
    set_name("oar");
    set_short("rowing oar");
    set_pshort("rowing oars");
    add_adj("rowing");
    set_long("It is a finely crafted oar.\n");

    set_hit(8);
    set_pen(12);
    
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, 10);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
