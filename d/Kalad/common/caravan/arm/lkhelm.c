#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("helm");
    set_adj("medium");
    add_adj("thanar");
    set_long("A standard-issue helmet for a Knight of Thanar. An image of "+
      "a dark sun is engraved upon the front.\n");
    set_ac(15);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_WEIGHT,2000);
}
