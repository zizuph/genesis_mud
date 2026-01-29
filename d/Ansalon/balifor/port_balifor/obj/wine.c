inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(20);
    set_name("wine");
    set_pname("wines");
    add_name("glass");
    add_pname("glasses");
    set_adj("elven");
    set_short("glass of elven wine");
    set_pshort("glasses of elven wine");
    set_long("A glass of fine, sweet tasting wine " +
	     "from Silvanesti.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
