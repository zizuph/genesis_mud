inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(20);
    set_name("wine");
    set_adj("sweet");
    set_short("sweet wine");
    set_pshort("sweet wines");
    set_long("You can smell the sweetness of this wine a foot away from you. It has a beautiful deep red color.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
