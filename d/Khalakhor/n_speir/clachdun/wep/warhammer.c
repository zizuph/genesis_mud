#include "local.h"
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/weapon";

void
create_khalakhor_weapon()
{
    set_name("warhammer");
    add_name(({"hammer","club"}));
    add_adj(({"oaken-shafted", "steel"}));
    set_short("oaken-shafted warhammer");
    set_long("This "+short()+" is has a massive steel head which "+
      "comes to a fine pick-like point at opposite end.  The head is "+
      "placed on top of a oaken shaft.\n");

    set_wt(W_CLUB);
    set_hit(29);
    set_pen(35);
    set_hands(W_ANYH);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_likely_break(3);
    set_likely_dull(7);
    set_likely_corr(9);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_POLEARM));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
    add_prop(CLACHDUN_GUARD_EQUIPMENT, 1);
}
