inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


inherit "/lib/keep";

void
create_armour()
{
    set_name("cloak");
    set_ac(6);
    set_at(A_ROBE);
    set_adj("fur");
    add_adj("heavy");
    set_short("heavy fur cloak");
    set_long("This heavy cloak is made from the furs of a great " +
      "white wolf. It is extremely thick, making it good protection " +
      "from the chill of winter and from the chill of death caused " +
      "by a steel sword.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}


