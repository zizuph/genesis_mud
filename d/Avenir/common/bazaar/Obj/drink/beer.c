inherit "/std/drink";
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <macros.h>

create_drink()
{
    set_name("beer");     
    add_name("bottle of beer");
    add_name("bottle");   

	set_short("beer");

    set_long("A bottle of fine tasting beer.\n");                     

	set_soft_amount(340);
    set_alco_amount(24);
    add_prop(OBJ_I_WEIGHT,340);
    add_prop(OBJ_I_VOLUME,340);
}
