/* Black Currant by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj(({"black", "shiny"}));
    set_herb_name("black currant");
    set_short("black shiny berry");
    set_pshort("black shiny berries");
    set_pname(({"berries", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a black shiny berry. It was probably " +
        "picked from a small shrub in a forest."));
    set_id_long(BSN("This is the berry of black currant, a shrub found " +
        "in temperate forests. Black currant (Ribes spp.) is a small " + 
        "shrub that has tiny prickles, reaching 1 cm in length. The " +
        "shrub itself grows to a height of 70 cm. The berries " +
        "are edible, giving a hungry adventurer some relief."));
    set_herb_value(40);
    set_id_diff(18);
    set_find_diff(4);
    set_effect(HERB_HEALING,"fatigue",4);
    set_decay_time(4500);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
