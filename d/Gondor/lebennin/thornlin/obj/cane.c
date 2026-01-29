inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"wooden cane","cane"}));
    set_short("wooden cane");
    set_pshort("wooden canes");
    set_long(BSN("This is a long wooden cane, it could be made of oak."));

    set_default_weapon(16,6,W_CLUB,W_BLUDGEON,W_RIGHT,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(16,6));
    add_prop(OBJ_I_WEIGHT,
      (F_WEIGHT_DEFAULT_WEAPON(16, W_CLUB) + random(200) - 100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
}

query_recover()
{
    return MASTER + ":" + query_wep_recover();
}
init_recover(arg)
{
    init_wep_recover(arg);
}
