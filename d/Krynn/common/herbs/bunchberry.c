/* Bunchberry by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"veined", "oval"}));
    set_herb_name("bunchberry");
    set_short("veined oval leaf");
    set_pshort("veined oval leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a veined oval leaf. It was probably " +
        "picked off an herb-like shrub in a forest."));
    set_id_long(BSN("This is the leaf of bunchberry, an herb-like shrub " + 
        "found in temperate forests. Bunchberry (Cornus canadensis) is a " +
        "shrub that grows to about 15cm high. It has many flowers, " +
        "subtended by 4 white involucral bracts. In the fall, it has a " +
        "tight cluster of red berries, all in a bunch. This herb can be " +
        "used to relieve tiredness."));
    set_herb_value(25);
    set_id_diff(7);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue",3);
    set_decay_time(5000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
