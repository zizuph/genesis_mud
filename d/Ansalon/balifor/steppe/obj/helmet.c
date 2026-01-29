inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("coif");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    set_adj("chainmail");
    set_long("This is a chainmail coif, head armourment " +
      "commonly worn by warriors.\n");
    set_short("chainmail coif");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));
}


