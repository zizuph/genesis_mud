/* Horsetail by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("stalk");
    set_adj(({"gritty", "slender"}));
    set_herb_name("horsetail");
    set_short("gritty slender stalk");
    set_pshort("gritty slender stalks");
    set_pname(({"stalks", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a gritty slender stalk. It was " +
        "probably picked in a forest or prairie."));
    set_id_long(BSN("This is a stalk of horsetail, an herb found in " +
        "temperate forests and plains. Horsetail (Equisetum spp.) is an " + 
        "herb that grows to about 60 cm high. This non-flowering plant " +
        "reproduces by spores. It has an alternative name, 'scouring " +
        "rush', as its slender gritty stalks can be used to clean pots. " +
        "The stalks have a high silica content, causing the grittiness. " +
        "It looks like it would hurt to eat this plant."));
    set_effect(HERB_HEALING,"hp",-50);
    set_herb_value(20);
    set_id_diff(3);
    set_find_diff(1);
    set_decay_time(10000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
