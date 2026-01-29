/* Cranberry by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj("red");
    set_herb_name("cranberry");
    set_short("red berry");
    set_pshort("red berries");
    set_pname(({"berries", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a red berry. It was probably " +
        "picked from a plant in a bog."));
    set_id_long(BSN("This is a cranberry, a berry from an herb found " +
        "in temperate bogs and fens. Cranberry (Oxycoccus palustris) " + 
        "is a small bog plant with shiny green leaves. It is said to " +
        "be useful in cleansing the urinary tract. Juices are made from " +
        "it, as is jelly. These have a tart taste."));
    set_herb_value(246);
    set_id_diff(12);
    set_find_diff(4);
    set_effect(HERB_CURING,"fatigue",51);
    set_decay_time(4000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
