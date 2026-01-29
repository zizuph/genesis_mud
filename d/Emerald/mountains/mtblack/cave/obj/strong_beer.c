/* A strong beer - coded 12/08/95 by Tulix III, based on the example */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("beer");
    set_adj("strong");
    set_long("This beer looks like it is brewed solely for the " +
             "pupose of getting someone drunk, and not worrying too " +
             "much about odd concepts such as 'flavour' " +
            "or 'texture'. In fact, it smells quite foul...!\n");
    set_soft_amount(350);
    set_alco_amount(18);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
}
