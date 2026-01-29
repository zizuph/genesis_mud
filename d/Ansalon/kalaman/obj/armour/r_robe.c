inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("cloak");
    set_ac(6);
    set_at(A_ROBE);
    set_adj("royal");
    set_short("royal cloak");
    set_long("This fine, royal red cloak is that usually " +
      "worn by the Lord of Kalaman.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
}


