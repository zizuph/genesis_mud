inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("helmet");
    set_ac(11);
    set_at(A_HEAD);
    set_am( ({ -4, -2, 6 }) );
    add_adj("military-looking");
    set_short("military-looking helmet");
    set_pshort("military-looking helmets");
    set_long("This military-looking helmet has a terrible smell of " +
             "hobgoblin associated with it. It's made out of some " +
             "sort of iron alloy, colouring it a flagrant green.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(11, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(11));
}
