#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("necklace");
    set_adj("gold");
    add_adj("chain");
    set_long("A long chain necklace made out of pure gold. Hanging from "+
      "the end is a pendant in the shape of a golden coin with rays "+
      "bursting forth from it.\n");
    set_ac(5);
    set_at(A_NECK);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_VOLUME,250);
    add_prop(OBJ_I_WEIGHT,500);
}
