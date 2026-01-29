inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(30);
    set_name("brandy");
    set_pname("brandies");
    add_name("mug");
    add_pname("mugs");
    set_adj(({"william's", "finest", "fine"}));
    set_short("mug of fine brandy");
    set_pshort("mugs of fine brandy");
    set_long("A mug of William Sweetwater's finest " +
	     "brandy, from the Pig and Whistle Inn in " +
	     "Port Balifor.\n");
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 250);
}
