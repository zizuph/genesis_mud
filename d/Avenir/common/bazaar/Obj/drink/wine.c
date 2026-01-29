inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

create_drink()
{
    set_name("strong wine");
    add_name("wine");
    add_name("bottle of wine");    
    add_name("bottle");            

   set_short("bottle of wine");
    set_long("A bottle of fine tasting wine.\n");   

	set_alco_amount(45);
    set_alco_amount(45);   /* 20% alcohol */
    add_prop(OBJ_I_WEIGHT,224);
    add_prop(OBJ_I_VOLUME,224);
}
