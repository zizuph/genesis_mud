#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("shoes");
    set_adj("work");
    set_short("pair of work shoes");
    set_pshort("pairs of work shoes");
    set_long("These leather shoes are worn and dusty, but durable and look " +
      "made to survive a hard day's work.\n");
    set_ac(8);
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 120);
}

