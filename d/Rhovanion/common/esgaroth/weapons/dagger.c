inherit "/d/Rhovanion/common/esgaroth/weapons/genericweapon";

#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("dagger");
    set_adj("curved");
    set_long("This is a wicked looking dagger, probably used mostly by " +
        "thieves and troublemakers since it is especially designed for " +  
        "close, silent fighting.\n");
    set_wt(W_KNIFE);
    set_pen(12);
    set_hit(16);
    set_dt(W_IMPALE);
}
