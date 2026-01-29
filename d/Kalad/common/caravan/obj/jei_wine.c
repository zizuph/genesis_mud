inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
    set_soft_amount(250);
    set_alco_amount(30);
    set_name("wine");
    set_adj("ruby");
    set_short("ruby wine");
    set_pshort("ruby wines");
    set_long("A wonderfully aromatic wine the color of blood. It sparkles "+
      "in the slightest of lights.\n");
    add_prop(HEAP_I_UNIT_WEIGHT, 250);
    add_prop(HEAP_I_UNIT_VOLUME, 250);
}
