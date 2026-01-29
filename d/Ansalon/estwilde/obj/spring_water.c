inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(500);
    set_name("water");
    add_name("flask");
    set_adj("spring");
    set_short("spring water");
    set_pshort("spring waters");
    set_long("This is a small flask of spring water. The water is cool and clear from a bubbling stream.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
