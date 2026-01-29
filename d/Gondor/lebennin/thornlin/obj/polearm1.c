#include "/d/Gondor/defs.h"
inherit WEP_DIR + "qstaff";

void
create_weapon()
{
    ::create_weapon();
    set_name("fork");
    set_adj("wooden");
    set_long(BSN("This is a long wooden fork, could be used as "+
	"a farming tool, or maybe as a polearm?"));
}
