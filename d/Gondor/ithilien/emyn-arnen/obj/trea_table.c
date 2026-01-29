
inherit "/std/container";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_container()
{
    set_short("stone table");
    set_name(({"stone", "rock", "block", "table"}));
    set_adj(({"large", "black", "stone", }));

    set_long(BSN(
        "A large black stone block, hewn from black rock and smoothly "
      + "polished. Standing in the middle of the room it was probably "
      + "meant to be used as a table."));

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(OBJ_I_VOLUME,   100000);
    add_prop(OBJ_I_WEIGHT,   500000);
    add_prop(CONT_I_VOLUME,  250000);
    add_prop(CONT_I_WEIGHT, 2000000);
    add_prop(CONT_I_ATTACH,       1);
}

