/* Comfrey by Elmore, Jul.20,2000  */
/* Special herb, used for a quest. */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj("dark-green");
    set_herb_name("comfrey");
    add_name("_comfrey_quest_herb_");
    set_short("dark-green leaf");
    set_pshort("dark-green leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a dark-green leaf. It's dark-green " +
        "color might indicate that it has been picked from a plant "+
        "that grows in a forest, and that it might only be found in "+
        "shade of some trees."));
    set_id_long(BSN("This is a comfrey, a very unusual leaf that can " +
        "only be found in partial shade in the forest of Krynn. "+
        "Comfrey (Symphytum) " + 
        "is a small plant with dark green leaves, the dark color "+
        "contract the suns rays more efficiently. It prefers to "+
        "grow in well-drained soils and in time, the plant can grow " +
        "to around 3 feet. It is known that if one carries Comfrey in "+
        "it will never get stolen, and some adventurers also use it "+
        "because it is said to grant them luck. It is wellknow that the "+
        "leaf will cure wounds and bruises is made into a tea, however "+
        "large amounts of can cause irreversible damage to the liver.\n"));
    set_herb_value(246);
    set_id_diff(13);
    set_find_diff(4);
    set_decay_time(2000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
