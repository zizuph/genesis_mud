inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("strong wine");
    add_name("wine");
    add_name("cup of wine");
    add_name("small cup of wine");
    add_name("cup of strong wine");
    add_name("small cup of strong wine");

    set_short("cup of strong wine");
    set_long(BS("This is the cheap stuff that's popular with the "+
      "vagrants in Twilight Park. The label reads:\n"+
      "     One Eyed Goblin\n"+
      "  For The Goblin in You\n"));

    set_soft_amount(224);   /* small cup - 8 ounces */
    set_alco_amount(45);   /* 20% alcohol */
    add_prop(OBJ_I_WEIGHT,224);
    add_prop(OBJ_I_VOLUME,224);
    add_prop(OBJ_I_VALUE,140);
    /* suggested price: 135cc */
}
