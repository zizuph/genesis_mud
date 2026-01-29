#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("scimitar");
    add_name("sword");
    set_adj("black");
    add_adj("steel");
    set_long("A viciously curved sword made entirely of night-black steel. "+
      "Even the sword's pommel is fashioned from the strangely black material.\n");
    set_hit(29);
    set_pen(24);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_VALUE,960);
    add_prop(OBJ_I_WEIGHT,6000);
    add_prop(OBJ_I_VOLUME,6000);
}
