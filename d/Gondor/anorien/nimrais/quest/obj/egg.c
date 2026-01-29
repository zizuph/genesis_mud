
inherit "/std/food";
#include "stdproperties.h"

create_food()
{
    set_name("egg");
    set_short("grey big egg");
    set_pshort("grey big eggs");
    set_adj(({"grey", "big" }));
    set_long("It is a big, grey egg. It looks quite much like a round rock, "
      + "but it's smoother and lighter.\n");
    set_amount(300);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop("_eagle_quest_egg", 1);

}

