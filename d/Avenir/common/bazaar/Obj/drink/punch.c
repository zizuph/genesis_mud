inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

create_drink()
{
    set_name("newbie punch");
    add_name("punch");

    set_short("cup of tangy punch");
    set_long("A cup of slightly spiked punch.");

	set_soft_amount(140);
	set_alco_amount(4);
    add_prop(OBJ_I_WEIGHT,140);
    add_prop(OBJ_I_VOLUME,140);
}
