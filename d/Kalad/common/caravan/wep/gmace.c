#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("mace");
    set_adj("keen");
    add_adj("steel");
    set_long("A large footman's mace that has been polished to a keen "+
      "brightness. It is obviously of some value to have been so "+
      "lovingly cared for.\n");
    set_hit(29);
    set_pen(21);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_VALUE,280);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,4000);
}
