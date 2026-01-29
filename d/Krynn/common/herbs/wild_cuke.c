/* Wild Cucumber by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("fruit");
    set_adj(({"prickly", "green"}));
    set_herb_name("wild cucumber");
    set_short("prickly green fruit");
    set_pshort("prickly green fruits");
    set_pname(({"fruits", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a prickly green fruit. It was probably " +
        "picked off a drooping vine near a riverbank."));
    set_id_long(BSN("This is a wild cucumber, a prickly green fruit found " +
        "along temperate riverbanks. Wild cucumber (Echinocystis lobata) " +
        "is a non-woody vine that entwines itself around trees and " +
        "shrubs. The fruit is edible, and may slightly aid tiredness."));
    set_herb_value(14);
    set_id_diff(27);
    set_find_diff(4);
    set_effect(HERB_HEALING,"fatigue",1);
    set_decay_time(6700);
    set_dryable();
    set_amount(5);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
