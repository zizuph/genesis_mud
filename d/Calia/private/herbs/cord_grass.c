/* Cord Grass by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"tall", "yellowish"}));
    set_herb_name("cord grass");
    set_short("tall yellowish leaf");
    set_pshort("tall yellowish leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a tall yellowish leaf. It was probably " +
        "picked from a salt marsh or near a beach."));
    set_id_long(BSN("This is the leaf of cord grass, an herb found " +
        "in salt marshes and near beaches. Cord grass (Spartina foliosa) " +
        "is one of the tallest beach grasses. It is usually partially " +
        "submerged. It is somehow able to excrete salt from the sea " +
        "water. Considering the salt content, it would not be a good " +
        "idea to eat this herb."));
    set_herb_value(24);
    set_id_diff(23);
    set_find_diff(2);
    set_effect(HERB_POISONING,"hp",15);
    set_decay_time(10000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
