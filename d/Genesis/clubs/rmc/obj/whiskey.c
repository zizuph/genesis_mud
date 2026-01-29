inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(15);
    set_name("whiskey");
    set_adj("glass of");
    set_short("glass of whiskey");
    set_pshort("glasses of whiskey");
    set_long("This is a glass of the finest whiskey you can buy "+
      "in the entire world.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
