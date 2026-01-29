/* Veronica by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"petite", "two-petalled"}));
    set_herb_name("veronica");
    set_short("petite two-petalled flower");
    set_pshort("petite two-petalled flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a petite two-petalled flower. It was " +
        "probably picked near a vernal pool in a forest."));
    set_id_long(BSN("This flower is called veronica. It is found in " +
        "and around temporary ponds within forests. Veronica " +
        "(Veronica catenata) is a small herb that grows to about 20 cm " +
        "high. Its flowers are odd in that they only have two petals. " +
         "It has no known use."));
    set_herb_value(14);
    set_id_diff(62);
    set_find_diff(2);
    set_decay_time(2300);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
