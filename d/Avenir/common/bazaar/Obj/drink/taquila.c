inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

create_drink()
{
    set_name("taquila");
    add_name("shot of taquila");

    set_short("shot of taquila");
    set_long("A shot of good taquila.");     

	set_soft_amount(0);
	set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
}
