/* Dandelion by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj("serrated");
    set_herb_name("dandelion");
    set_short("serrated leaf");
    set_pshort("serrated leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a serrated leaf. It was probably " +
        "picked from a roadside area or near a disturbed area."));
    set_id_long(BSN("This is the leaf of a dandelion, an herb found " +
        "in temperate open areas. Dandelion (Taraxacum officinale) is an " +
        "herb that develops yellow blossoms, then finally a many-seeded " +
        "head, each seed with a 'parachute' that can be carried by the " +
        "wind. The leaves of the dandelion are edible and provide some " +
        "respite, while the roots can be used to make a bitter wine."));
    set_herb_value(62);
    set_id_diff(3);
    set_find_diff(1);
    set_effect(HERB_HEALING,"fatigue",5);
    set_decay_time(4000);
    set_dryable();
    set_amount(5);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
