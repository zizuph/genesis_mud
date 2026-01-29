#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    add_name("sauthacuith_ingr1");
    set_adj(({"little", "blue", }));
    set_short("little blue berry");
    set_pshort("little blue berries");
    set_herb_name("attanar");
    set_id_long(BSN("This blue berry is an example of the Attanar " +
		    "herb species. It can be eaten, and will have a " +
		    "healing effect on your body.")); 
    set_unid_long(BSN("This blue berry looks like an ordinary berry. You "
		+ "do not know what it is for."));
    set_ingest_verb("eat");
    set_id_diff(35);
    set_find_diff(8);
    set_effect(HERB_HEALING, "hp", 72);
    set_decay_time(1800);
    set_herb_value(1728);
}

