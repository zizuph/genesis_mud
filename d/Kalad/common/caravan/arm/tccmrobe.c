#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("robe");
    set_adj("courtly");
    set_long("A finely woven robe made of the most expensive of silks. By the "+
      "symbol of the golden coin in front, you realize that this must belong to "+
      "one of the council members of the Trading Company.\n");
    set_ac(4);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,600);
    add_prop(OBJ_I_VOLUME,1200);
    add_prop(OBJ_I_WEIGHT,1200);
}
