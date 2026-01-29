#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("platemail");
    set_adj("thanar");
    set_long("A large, sturdy-looking suit of mail armour. On the breastplate "+
      "an image of a dark sun is engraved.\n");
    set_ac(30);
    set_am(({0,-3,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,900);
    add_prop(OBJ_I_WEIGHT,17500);
    add_prop(OBJ_I_VOLUME,17500);
}
