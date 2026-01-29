/* Chantrelle by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("mushroom");
    set_adj(({"puffy", "yellow"}));
    set_herb_name("chantrelle");
    set_short("puffy yellow mushroom");
    set_pshort("puffy yellow mushrooms");
    set_pname("chantrelles");
    add_pname(({"mushrooms", "herbs"}));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a puffy yellow mushroom. It was " +
        "probably picked from a forest floor."));
    set_id_long(BSN("This is a chantrelle, an edible mushroom found " +
        "in temperate forests. Chantrelle is a fungus that grows to " + 
        "about 5 cm high. Members of this genus are characterized by " +
        "their simplicity. This puffy yellow mushroom has no special " +
        "features other than its soft texture and soft yellow-orange " +
        "colour. It is said to be good for the mind."));
    set_effect(HERB_HEALING,"mana",13);
    set_herb_value(160);
    set_id_diff(25);
    set_find_diff(9);
    set_decay_time(2000);
    set_dryable();
    set_amount(2);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
