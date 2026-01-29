inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

void
create_armour()
{
    set_name("helm");
    set_adj(({"plate","great"}));
    set_short("great plate helm");
    set_long("This "+short()+" looks like its seen a few battles.  "+
      "It looks a bit worn but well maintained.  The helm looks like "+
      "it is well made and could protect your head from a good many blows.\n");

    set_at(A_HEAD);
    set_ac(28);
    set_am(({-1, 1, 0}));
    set_likely_break(9);
    set_likely_cond(7);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(28, A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(28) + random(25));
}
