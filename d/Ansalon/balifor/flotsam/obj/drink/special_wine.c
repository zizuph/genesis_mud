inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(100);
    set_name("wine");
    add_name("barrel");
    set_adj("fine");
    set_short("small barrel of fine wine");
    set_pshort("small barrels of fine wine");
    set_long("This small redwood barrel is used to hold wine of some " +
      "sort. It looks like the barrel is quite old, and has been up until recently well taken care of. " +
      "A fancy label on the side reads 'Peak aging at the year 351'.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
