
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(90);
    set_alco_amount(30);
    set_name("whiskey");
    add_name("shot");
    add_name("shot of whiskey");

    set_short("shot of whiskey");
    set_pshort("shots of whiskey");

    set_long("A truly wicked looking beverage.\n");
   
    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_I_VOLUME, 120);
}
