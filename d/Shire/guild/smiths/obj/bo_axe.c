/*            bores axe            */

inherit "/std/weapon";

#include <wa_types.h>    
#include <stdproperties.h>
#include "smiths.h"

void
create_weapon()
{
    set_name("axe");
    set_short("two-handed steel axe");
   set_long("This is a two-handed steel axe of excellent make. You notice"+
       " that the hilt is wrapped with leather from a wolf skin. Golden"+
       " runes are running along the superbly forged steel blade. The runes"+
       " say: I, Bores, forged this axe. Death upon he who wields it with"+
       "out honour.\n");

    set_adj("steel");
    set_adj("two-handed");

    set_hit(40);
    set_pen(40);

    set_wt(W_AXE);
    set_dt(W_SLASH);

    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
