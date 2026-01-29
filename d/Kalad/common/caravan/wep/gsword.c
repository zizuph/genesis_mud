#include "../default.h"
inherit (STD + "weapon");

#include <formulas.h>
#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("sword");
    set_adj("keen");
    add_adj("short");
    set_long("This short sword possesses a keen, razor-sharp edge that looks "+
      "excellent for cutting flesh to ribbons.\n");
    set_hit(20);
    set_pen(23);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 23));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}
