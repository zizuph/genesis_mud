inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

void
create_armour()
{
    set_name("helm");
    set_adj(({"plate","dented"}));
    set_short("dented plate helm");
    set_long("This "+short()+" looks like its seen a few battles.  "+
      "A bit worn and dented but it still looks like it could provide "+
      "good protection.\n");

    set_at(A_HEAD);
    set_ac(21);
    set_am(({-1, 1, 0}));
    set_condition(3);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(21, A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21) + random(25));
}
