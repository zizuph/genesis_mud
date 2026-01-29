/* Fucus by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"warty", "air-filled"}));
    set_herb_name("fucus");
    set_short("air-filled warty alga");
    set_pshort("air-filled warty algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an air-filled warty alga. It was probably " +
        "picked nearshore or in the intertidal zone."));
    set_id_long(BSN("This is a air-filled warty alga, an herb found " +
        "in nearshore oceans and intertidal areas. Fucus rockweed " +
        "(Fucus spp.) is a greenish brown colour. It is commonly called  " +
        "rockweed, due to its omnipresence on tidal rocks. The surface " +
        "of the alga is covered with what appear to be warts, but are " +
        "actually specialized structures. This herb appears to be mildly " +
        "edible."));
    set_herb_value(22);
    set_id_diff(7);
    set_find_diff(1);
    set_effect(HERB_HEALING,"fatigue",2);
    set_decay_time(4000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
