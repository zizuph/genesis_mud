/* Locoweed by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"purple", "hoary"}));
    set_herb_name("locoweed");
    set_short("purple hoary flower");
    set_pshort("purple hoary flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a purple hoary flower. It was " +
        "probably picked from a sunny prairie."));
    set_id_long(BSN("This is a flower of locoweed, a legume found " +
        "in temperate prairies. Locoweed (Oxytropis splendens) is an " + 
        "herb that grows to about 25 cm high. The flower is both hoary " +
        "and purple, in a dense spike. It has a thick rootstock, like " +
        "most other prairie plants. From the name, you'd assume that this " +
        "plant is poisonous, probably to the mind."));
    set_effect(HERB_POISONING,"mana",30);
    add_effect(HERB_HEALING,"mana",-150);
    set_herb_value(20);
    set_id_diff(45);
    set_find_diff(4);
    set_decay_time(2300);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
