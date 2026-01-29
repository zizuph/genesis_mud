inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

create_drink()
{
    set_name("whiskey");
    add_name("shot of whiskey");

    set_short("shot of whiskey");
    set_long("Strong stuff! You know what to do.\n");
	set_soft_amount(50);
	set_alco_amount(40);
    add_prop(OBJ_I_VOLUME,50);
	add_prop(OBJ_I_WEIGHT,50);
}
