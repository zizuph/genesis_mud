/* Sarsaparilla by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("root");
    set_adj(({"pliable", "licorice-scented"}));
    set_herb_name("sarsaparilla");
    set_short("licorice-scented pliable root");
    set_pshort("licorice-scented pliable roots");
    set_pname(({"roots", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a licorice-scented pliable root. It was " +
        "probably picked from a 5-pinnate-leaved herb in a forest."));
    set_id_long(BSN("This is sarsaparilla, a 5-pinnate-leaved herb found " +
        "in temperate forests. Sarsaparilla (Aralia nudicaulis) is a " + 
        "herb that grows to about 75 cm high. The herb has a licorice-" +
        "scented pliable root that is used both as a food source and as " +
        "a flavouring for non-alcoholic beverages."));
    set_herb_value(20);
    set_id_diff(16);
    set_find_diff(6);
    set_decay_time(5000);
    set_dryable();
    set_amount(25);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
