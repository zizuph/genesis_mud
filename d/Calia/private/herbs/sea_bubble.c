/* Sea Bubble by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"globular", "yellow"}));
    set_herb_name("sea bubble");
    set_short("globular yellow alga");
    set_pshort("globular yellow algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a globular yellow alga. It was probably " +
        "picked from an intertidal pool or shallow ocean."));
    set_id_long(BSN("This is a globular yellow alga, an herb found " +
        "in intertidal pools and shallow ocean waters. Sea bubble " +
        "(Colpomenia sinuosa) is a small alga that is typically 2-5 cm in " +
        "diameter. The name of sea bubble is derived from the fact that " +
        "the alga captures oxygen in large cavities. Eating this herb " +
        "is said to heal small wounds."));
    set_herb_value(220);
    set_id_diff(12);
    set_find_diff(5);
    set_effect(HERB_HEALING,"hp",5);
    set_decay_time(2000);
    set_amount(1);
}

void
special_effect()
{
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
