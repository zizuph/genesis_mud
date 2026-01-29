/* Salt Wort by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"succulent", "rotund"}));
    set_herb_name("salt wort");
    set_short("succulent rotund leaf");
    set_pshort("succulent rotund leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a succulent rotund leaf. It was probably " +
        "picked from shallow water or exposed mudflat area near an ocean."));
    set_id_long(BSN("This is the leaf of salt wort, an herb found " +
        "in shallow water or exposed mudflat areas near oceans. Salt wort " +
        "(Batis maritina) is a flowering plant that grows horizontally " +
        "along the substrate, sending out runners. The fleshy leaves " +
        "arise from these runners. Consuming this herb would cause much " +
        "mental pain, so the old-timers say."));
    set_herb_value(16);
    set_id_diff(24);
    set_find_diff(7);
    set_effect(HERB_HEALING,"mana",-100);
    set_decay_time(3200);
    set_dryable();
    set_amount(2);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
