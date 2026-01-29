inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(20);
    set_name("ale");
    set_adj("dwarven");
    set_short("dwarven ale");
    set_long("Dwarven ale, one of the finest beverages " +
      "to come from that race.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
