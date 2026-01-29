#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("helm");
    set_adj("light");
    add_adj("banded");
    set_long("A light helmet made of banded armour. Despite its lack "+
      "of heaviness it still seems capable of providing more than adequate "+
      "protection for its wearer. An image of a golden lion is engraved "+
      "upon it.\n");
    set_ac(12);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,2000);
}
