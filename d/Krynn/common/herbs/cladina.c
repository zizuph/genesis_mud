/* Cladina by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("lichen");
    set_adj(({"coral-like", "grey"}));
    set_herb_name("cladina");
    set_short("coral-like grey lichen");
    set_pshort("coral-like grey lichens");
    set_pname(({"lichens", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a coral-like grey lichen. It was probably " +
        "picked from a sunny forest floor."));
    set_id_long(BSN("This lichen is called cladina. It is found in " +
        "hemi-spherical clusters that look much like coral. This species " +
        "of cladina is grey, but there exists a yellow one as well. " +
        "This lichen covers the forest floor of jack pine and spruce " +
        "forests in the temperate zone. It is edible, and provides a " +
        "boost in one's health."));
    set_herb_value(930);
    set_id_diff(47);
    set_find_diff(7);
    set_effect(HERB_ENHANCING,"con",25);
    add_effect(HERB_HEALING,"hp",40);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
