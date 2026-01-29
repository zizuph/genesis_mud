inherit "/d/Rhovanion/common/esgaroth/weapons/genericweapon";

#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("fisher's");
    set_long("This looks like a fisherman's knife, more useful for gutting " +
        "fish than gutting people.\n");
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_pen(9);
    set_hit(11);
}
