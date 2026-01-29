inherit "/d/Kalad/std/missile_launcher_std";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
#include <formulas.h>


void
create_missile_launcher()
{
    set_name("bow");
    add_adj(({"wooden","short"}));
    set_short("wooden short bow");

    set_long("This is a short wooden bow made of black yarrow wood. "+
    "It looks rather well made, with a tight horse-tail string.\n");

    set_hit(30);
    set_pen(28);

    set_dt(W_IMPALE);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,28) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(30,W_MISSILE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    set_holder_type("quiver");
    set_missile_type("arrow");
    set_reload_time(2);

}
