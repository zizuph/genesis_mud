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
    add_adj("short-horned dwarven");
    set_long("This helmet is decorated by a pair of stubby horns, " +
             "and has a nose guard to protect from blows to the face. " +
             "It is clearly a decent piece of headgear.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(11, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(11));
}
