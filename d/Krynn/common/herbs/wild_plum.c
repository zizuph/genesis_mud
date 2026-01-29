/* Wild Plum by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("fruit");
    set_adj(({"smooth", "purplish"}));
    set_herb_name("wild plum");
    set_short("smooth purplish fruit");
    set_pshort("smooth purplish fruits");
    set_pname(({"fruits", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a smooth purplish fruit. It was probably " +
        "picked off a prickly shrub near a forest."));
    set_id_long(BSN("This is a wild plum, a smooth purplish fruit found " +
        "in temperate forests. Wild plum (Prunus nigra) is a shrub " +
        "that grows to about 3 meters high. The shrub has sweet-scented " +
        "blossoms, white in colour. However, the branches of the shrub " +
        "have numerous thorns. The fruit of the shrub is said to refresh " +
        "a weary soul."));
    set_herb_value(56);
    set_id_diff(9);
    set_find_diff(6);
    set_effect(HERB_HEALING,"fatigue",4);
    set_decay_time(4000);
    set_dryable();
    set_amount(10);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
