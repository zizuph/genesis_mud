#include "local.h"
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/weapon";

void
create_khalakhor_weapon()
{
    set_name("spear");
    add_name(({"polearm", "weapon"}));
    add_adj(({"steel-tipped", "long"}));
    set_short("long steel-tipped spear");
    set_long("This "+short()+" seems to be a "+query_name()+" of "+
      "above average quality.  The "+query_adjs()[0]+" point at the "+
      "end of the shaft seems to be razor sharp and capable of "+
      "puncturing all but the heaviest of armours.\n");

    set_wt(W_POLEARM);
    set_hit(28);
    set_pen(32);
    set_hands(W_RIGHT);
    set_dt(W_IMPALE);
    set_likely_break(12);
    set_likely_dull(3);
    set_likely_corr(9);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_POLEARM));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
}
