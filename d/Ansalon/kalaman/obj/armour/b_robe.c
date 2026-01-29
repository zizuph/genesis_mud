inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("robe");
    set_ac(4);
    set_at(A_ROBE);
    set_adj("blue");
    set_short("blue robe");
    set_long("This robe is made of wool dyed sky blue. " +
      "It is rather thick, and offers some protection " +
      "from the cold.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
}


