inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

void
create_armour()
{
    set_name("boots");
    set_adj(({"black","sturdy"}));
    set_short("pair of sturdy black boots");
    set_pshort("pairs of sturdy black boots");
    set_long(capitalize(LANG_ASHORT(this_object())) +" made of leather.  "+
      "Light and warm, these boots would keep your toes cozy even in "+
      "the most unpleasant of weather.\n");

    set_at(A_FEET);
    set_ac(12);
    set_am(({-2, -3, 5}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(12, A_FEET));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12) + random(25));
}
