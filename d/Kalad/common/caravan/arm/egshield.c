#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("shield");
    set_adj("encovering");
    add_adj("white");
    set_long("A shield so large it could almost qualify as a body shield, "+
      "yet it is still small enough to be held in one hand. An engraved "+
      "image of a golden lion has been etched onto its front.\n");
    set_ac(19);
    set_at(A_SHIELD);
    add_prop(OBJ_I_VALUE,450);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,2000);
}
