inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"


create_weapon() {
   set_name("morningstar");
   add_name("club");
   set_short("huge spiked morningstar");
   set_pshort("huge spiked morningstar");
   set_adj(({"huge", "spiked"}));
   set_long("This is a huge spiked morningstar. It is a long " +
        "pole with a chain at the top and a spiked ball at the " +
        "end of the chain. It's a deadly weapon and inflicts quite " +
        "a bit of pain when used properly. It's a favorite of " +
        "trolls and quite common.\n");
   set_hit(35);
   set_pen(35);
   set_wt(W_CLUB);
   set_dt(W_IMPALE | W_BLUDGEON);
   add_item(({"spikes","spike","clubs spikes", "clubs spike"}),
        "They seems awful! You wouldn't be hit by them.\n");
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}
