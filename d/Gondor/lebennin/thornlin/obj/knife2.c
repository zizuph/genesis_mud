/* A knife  */
#include "/d/Gondor/defs.h"
inherit WEP_DIR + "knife";

void
create_weapon()
{
    ::create_weapon();

    set_name("knife");
    remove_adj(query_adjs());
    set_adj(({"small","sharp",}));
    set_pname("knives");
    set_long(BSN("This is a small knife, with a somewhat long hilt "+
	"and a short blade (though sharp), it makes it look "+
	"a bit funny but it would probably make a fine working "+
	"knife. The hilt is formed so it probably would lie "+
	"great in your hand."));
}
