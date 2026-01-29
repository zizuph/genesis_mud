inherit "/std/weapon";

#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("battleaxe");
    set_adj(({"polished","steel", "dwarven"}));
    set_short("polished dwarven battleaxe");
    add_name(({"axe","battle-axe"}));
    set_long("This "+short()+" is a sturdy well build weapon of "+
      "dwarven make.  It looks like it would do some hefty damage if "+
      "you connected with it.\n");

    set_wt(W_AXE);
    set_hit(40);
    set_pen(45);
    set_hands(W_BOTH);
    set_dt(W_IMPALE);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_AXE) + random(300));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28,35) + 20 + random(41));
}
