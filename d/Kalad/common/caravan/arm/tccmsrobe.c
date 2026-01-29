#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("robe");
    set_adj("elegant");
    set_long("A finely woven and elegantly designed robe. Created from "+
      "the finest of silks it has been intricately designed with a myriad "+
      "variety of symbols, the most prominent of which is the symbol of the "+
      "golden coin, which marks this as belonging to an important member of "+
      "the Trading Company council.\n");
    set_ac(4);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,720);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_WEIGHT,1400);
}
