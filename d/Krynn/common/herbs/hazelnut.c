/* Hazelnut by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("nut");
    set_adj(({"hard", "enbracted"}));
    set_herb_name("hazelnut");
    set_short("hard enbracted nut");
    set_pshort("hard enbracted nuts");
    set_pname(({"nuts", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a hard enbracted nut. It was probably " +
        "picked off a meter high shrub in a forest."));
    set_id_long(BSN("This is a hazelnut, a hard enbracted nut found " +
        "in temperate forests. Hazelnut (Corylus cornuta) is a shrub " +
        "that grows to about 1 meter high. The shrub has minute " +
        "blossoms that flower early in the spring. Its leaves are a " +
        "favourite of cultured adventurers. The nut of the shrub is said " +
        "to refresh and feed a tired traveller."));
    set_herb_value(56);
    set_id_diff(14);
    set_find_diff(3);
    set_effect(HERB_HEALING,"fatigue",2);
    set_decay_time(10000);
    set_dryable();
    set_amount(2);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
