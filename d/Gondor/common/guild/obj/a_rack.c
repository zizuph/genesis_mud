inherit "/std/container";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_container()
{
    set_short("armour rack");
    set_name("rack");
    add_name("armour rack");
    set_adj("armour");
    set_long(BSN("The armour rack is made to contain armours. "
      + "It looks very massive and can probably hold the equipment "
      + "for several Rangers."));

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

}

