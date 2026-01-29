inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{

    set_name("gown");
    add_name("_dress_");
    set_adj("beautiful");
    add_adj("flowing");
    set_short("beautiful flowing gown");
    set_long("This magnificent gown can only be owned by a lady " +
      "who is noble or extremely rich. The fabric itself looks " +
      "expensive enough to buy a small farm.\n");
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 5000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
}
