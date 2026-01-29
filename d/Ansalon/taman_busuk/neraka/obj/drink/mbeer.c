
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(12);
    set_name("beer");
    add_name("mug of beer");
   
    set_short("mug of beer");
    set_pshort("mugs of beer");
    set_long("It's not the finest beer ever to be brewed, " +
		"but it will do.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
