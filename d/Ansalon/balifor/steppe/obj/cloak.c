inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("cloak");
    set_ac(3);
    set_at(A_ROBE);
    set_adj("dusty");
    set_short("dusty cloak");
    set_long("This is a simple travellers cloak, dusty from " +
      "plenty of travel.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}


