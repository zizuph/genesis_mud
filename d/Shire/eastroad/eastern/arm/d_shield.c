inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

void
create_armour()
{
    set_name("shield");
    set_adj(({"large","wooden","mirthil","re-enforced"}));
    set_short("large wooden shield");
    set_long("This "+short()+" is a extremely well built shield that has "+
      "been re-enforced with mithril, making it more durable and protective.  "+
      "The size of the shield makes it possible to protect a larger area of "+
      "your body, than if it were a normal sized shield.\n");

    set_at(A_SHIELD);
    set_ac(25);
    set_am(({-2, -1, 3}));
    set_likely_break(5);
    set_likely_cond(17);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + 100 + random(300));
}

public int *
query_shield_slots()
{
    return ::query_shield_slots() + ({A_TORSO});
}
