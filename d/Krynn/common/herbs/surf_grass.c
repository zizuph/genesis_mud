/* Surf Grass by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"slender", "green"}));
    set_herb_name("surf grass");
    set_short("slender green leaf");
    set_pshort("slender green leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a slender green leaf. It was probably " +
        "picked from the intertidal zone of some ocean."));
    set_id_long(BSN("This is the leaf of surf grass, an herb found " +
        "in the intertidal zones of oceans. Surf grass (Phyllospadix spp.) " +
        "is a small grass, 15 cm high, that grows and reproduces " +
        "completely submerged. It is somehow able to excrete salt from " +
        "the sea water. Considering the salt content, it would not be a " +
        "good idea to eat this herb, as it may make you feel very tired."));
    set_herb_value(18);
    set_id_diff(12);
    set_find_diff(4);
    set_effect(HERB_POISONING,"fatigue",15);
    add_effect(HERB_HEALING,"fatigue",-30);
    set_decay_time(8600);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
