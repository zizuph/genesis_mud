#include "/d/Gondor/defs.h"
inherit ARM_DIR + "ltrousers";

void
create_armour()
{
    ::create_armour();
    set_name("trousers");
    set_adj("new");
    set_short("pair of new trousers");
    set_pshort("pairs of new trousers");
    set_long(BSN("These trousers seem to be fairly new, and would give "+
	"some protection."));
}
