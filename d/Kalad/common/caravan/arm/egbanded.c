#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("mail");
    set_adj("light");
    add_adj("banded");
    set_long("A fairly light set of banded mail armour, perfect for "+
      "protecting its wearer from bodily harm. An image of a golden lion "+
      "is engraved upon it.\n");
    set_ac(25);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,650);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_WEIGHT, 8000);
}
