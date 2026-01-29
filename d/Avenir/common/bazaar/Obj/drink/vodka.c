inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

create_drink()
{
    set_name("vodka");              
    add_name("shot of vodka");

    set_short("shot of vodka");     
    set_long("A shot of strong vodka. It smells very strong.\n");         

	set_soft_amount(50);
	set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
}
