#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("mail");
    set_adj("thanar");
    add_adj("banded");
    set_long("Armor made of overlapping strips of metal sewn onto a "+
      "backing of chain mail. Upon the breastplate, an image of a dark sun "+
      "has been engraved.\n");
    set_ac(27);
    set_am(({0,-5,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,480);
    add_prop(OBJ_I_VOLUME,12000);
    add_prop(OBJ_I_WEIGHT,12000);
}
