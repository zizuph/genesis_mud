inherit "/std/drink";
#include "/sys/stdproperties.h"

void
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(0);
    set_name("cup");
    add_name("cup of coffee");
    add_name("coffee");
    set_adj("gnomish");
    set_short("cup of coffee");
    set_pshort("cups of coffee");
    set_long("A cup filled with a hot, " 
        + ({"dark brown", "black", "nearly transparent"
                , "light brown", "tasty"})[random(5)] 
        + " liquid.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
