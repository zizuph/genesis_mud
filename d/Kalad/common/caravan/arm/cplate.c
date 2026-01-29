#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("mail");
    set_adj("full");
    add_adj("plate");
    set_long("This platemail armour seems to be made out of pure steel, "+
      "obviously marking it as very expensive and very durable. A figure "+
      "of a golden camel is visible on the front of the armour, marking it "+
      "as the captain of the city guards' armour.\n");
    set_ac(35);
    set_am(({0,3,5}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 1020);
    add_prop(OBJ_I_VOLUME,10000);
    add_prop(OBJ_I_WEIGHT, 20000);
}
