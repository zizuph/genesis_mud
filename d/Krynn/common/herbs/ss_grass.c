/* Seaside Grass by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"green", "scratchy"}));
    set_herb_name("seaside grass");
    set_short("scratchy green leaf");
    set_pshort("scratchy green leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a scratchy green leaf. It was probably " +
        "picked from a salt marsh or on a beach dune."));
    set_id_long(BSN("This is the leaf of seaside grass, an herb found " +
        "in salt marshes and on beaches. Seaside grass is a tall beach " +
        "grass, offering stability to the easily eroded sand dunes. " +
        "Its flowers have brilliant yellow stamens, covered with pollen. " +
        "The leaf is edible, apparently causing some sort of beneficial " +
        "reactions in those plagued by fatigue."));
    set_herb_value(192);
    set_id_diff(13);
    set_find_diff(4);
    set_effect(HERB_CURING,"fatigue",32);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
