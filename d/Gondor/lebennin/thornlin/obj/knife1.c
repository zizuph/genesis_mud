/* A knife  */
#include "/d/Gondor/defs.h"
inherit WEP_DIR + "knife";

void
create_weapon()
{
    ::create_weapon();

    set_name("knife");
    remove_adj(query_adjs());
    set_adj(({"sharp", "long",}));
    set_pname("knives");
    set_long(BSN("It is a very simple looking knife, "+
	"with a beech hilt and a long sharp steel blade. "+
	"It seems like it has been used alot."));
}
