#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("chainmail");
    set_adj("thanar");
    set_long("A finely crafted suit of chainmail armour. Upon the "+
      "breastplate an image of a dark sun has been engraved.\n");
    set_ac(25);
    set_am(({0,-5,0}));
    add_prop(OBJ_I_VALUE,420);
    add_prop(OBJ_I_VOLUME,9000);
    add_prop(OBJ_I_WEIGHT,9000);
}
