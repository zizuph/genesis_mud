#include "/d/Gondor/defs.h"
inherit (WEP_DIR + "qstaff");

void
create_weapon()
{
    ::create_weapon();
    set_name("staff");
    set_adj("long");
    set_long(BSN("This is a long wooden staff, could be used as "+
	"walking gear, or maybe as a polearm."));
}
