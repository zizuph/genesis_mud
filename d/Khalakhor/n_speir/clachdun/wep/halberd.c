#include "local.h"
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/weapon";

void
create_khalakhor_weapon()
{
    set_name("halberd");
    add_name(({"polearm", "weapon"}));
    add_adj(({"curved", "steel"}));
    set_short("curved steel halberd");
    set_long("This "+short()+" looks like it could do considerable "+
      "damage with its curved steel axe-head.   On the head of the "+
      "wooden shaft is a long spear point which is used when in "+
      "formation with other halberdiers or spearmen.\n");

    set_wt(W_POLEARM);
    set_hit(31);
    set_pen(39);
    set_hands(W_BOTH);
    set_dt(W_SLASH | W_IMPALE);
    set_likely_break(5);
    set_likely_dull(12);
    set_likely_corr(12);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_POLEARM));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
}
