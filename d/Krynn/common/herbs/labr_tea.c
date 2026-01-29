/* Labrador Tea by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"rusty", "fuzzy"}));
    set_herb_name("labrador tea");
    set_short("fuzzy rusty leaf");
    set_pshort("fuzzy rusty leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a fuzzy rusty leaf. It was probably " +
        "picked from somewhere near a bog or fen."));
    set_id_long(BSN("This is the leaf of labrador tea, an herb found " +
        "in temperate bogs and fens. Labrador tea (Ledum groenlandicum) " +
        "is a shrubby herb that has white flowers. The leaves are glossy " +
        "green on top, but have a rusty-coloured fuzz on the bottom. " +
        "Tea can be made from the leaves, but it must be twice-boiled " +
        "or else the poisons in the leaf will cause it to be bitter and " + 
        "result in fatigue."));
    set_herb_value(42);
    set_id_diff(10);
    set_find_diff(3);
    set_effect(HERB_POISONING,"fatigue",15);
    set_decay_time(8000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
