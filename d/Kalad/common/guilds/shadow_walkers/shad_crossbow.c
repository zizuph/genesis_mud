inherit "/d/Kalad/std/missile_launcher_std";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
#include <formulas.h>


void
create_missile_launcher()
{
    set_name("crossbow");
    add_adj(({"deadly","hand"}));
    set_short("deadly hand crossbow");

    set_long("A small crossbow that is compact. It is fasioned by "+
    "wood and steel, and painted black. It looks rather deadly, even "+
    "given its small size. You must use it with both hands, however.\n");

    set_hit(30);
    set_pen(30);

    set_dt(W_IMPALE);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,28) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(30,W_MISSILE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    set_holder_type("quiver");
    set_missile_type("quarrel");
    set_reload_time(3);

}
