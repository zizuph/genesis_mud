#include "/d/Gondor/defs.h"
inherit EMYN_ARNEN_DIR + "obj/arawhorn";

#include "../ox_quest.h"

void
create_object()
{
    set_name("horn");
    add_name(THORNLIN_OX_HUNTING_HORN);
    add_adj("long");
    set_long(BSN("Originally this was a horn from the great Kine of "
	+ "Araw. Now someone has hollowed the horn out and made it "
	+ "into a fine hunting horn. It is possible to produce a sound "
	+ "by blowing into the horn.")); 
}

