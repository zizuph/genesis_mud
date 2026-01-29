#include "/d/Gondor/defs.h"
inherit ARM_DIR + "ltrousers";

void
create_armour()
{
    set_name("trousers");
    set_adj("dirty");
    set_short("pair of dirty trousers");
    set_pshort("pairs of dirty trousers");
    set_long(BSN("These trousers seem to have been worn day out "+
	"and day in for many years."));
}
