#include "local.h"
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/weapon";

void
create_khalakhor_weapon()
{
    set_name("axe");
    add_name(({"battleaxe","weapon"}));
    add_adj(({"wicked", "sharp","steel"}));
    set_short("wicked steel battleaxe");

    set_wt(W_AXE);
    set_hit(32);
    set_pen(34);
    set_hands(W_RIGHT);
    set_dt(W_SLASH | W_IMPALE);
    set_likely_break(7);
    set_likely_dull(7);
    set_likely_corr(14);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_AXE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
}
