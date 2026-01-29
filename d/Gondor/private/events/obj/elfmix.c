inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_food()
{
    set_name(({"chip", "mix", "trailmix", "_gondor_trail_mix_"}));
    set_adj("dried");
    add_adj("gondorian");
    add_adj("elf");
    set_short("dried gondorian elf chip");
    set_long("This dried gondorian elf chip would fit in nicely in some " +
        "trailmix.\n");
    set_amount(10);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);

}

