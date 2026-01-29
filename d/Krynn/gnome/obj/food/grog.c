inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(250);
    set_alco_amount(20);
    set_name("grog");
    add_name("mug");
    set_adj("Dwarvish");
    set_short("mug of Dwarvish grog");
    set_pshort("mugs of Dwarvish grog");
    set_long("Brewed mostly for clout, but not a bad taste really." +
	"  Besides, after\na few mugs, who cares?\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
