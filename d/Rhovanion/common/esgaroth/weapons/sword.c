inherit "/d/Rhovanion/common/esgaroth/weapons/genericweapon";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("sword");
    set_adj("lakeman's");
    set_long("This sword is typical of the lakemen: slightly longer than " +
        "normal to allow a better reach from the small ships, but lighter " +
        "since weight is crucial to them.\n");
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_pen(15);
    set_hit(15);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 600);
}
