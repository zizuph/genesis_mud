inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

void
create_armour()
{
    set_name("hauberk");
    set_adj(({"silver","doublemail"}));
    set_short("silver doublemail hauberk");
    set_long("This "+short()+" looks like it would offer good protection from "+
      "blows in combat.  No visible weaknesses can be seen between the layers "+
      "of chainmail which make up this piece of armour.\n");

    set_at(A_TORSO);
    set_ac(29);
    set_am(({-1, 1, 0}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(29, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(29) + 75 + random(125));
}
