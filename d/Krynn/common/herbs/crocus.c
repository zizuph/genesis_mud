/* Crocus by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"pale", "purplish"}));
    set_herb_name("crocus");
    set_short("pale purplish flower");
    set_pshort("pale purplish flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a pale purplish flower. It was " +
        "probably picked from a sunny open area."));
    set_id_long(BSN("This is the flower of a crocus, an anemone found " +
        "in temperate sunny meadows. Crocus (Anemone patens) is an " + 
        "herb that grows to about 30 cm high. The flower is hoary, " +
        "and it is splashed with a pale purplish colour. The sexual " +
        "floral parts are a bright yellow. As with most members of the " +
        "Anemone genus, any part of the crocus is mildly poisonous."));
    set_effect(HERB_POISONING,"mana",20);
    add_effect(HERB_HEALING,"hp",-20);
    set_herb_value(32);
    set_id_diff(25);
    set_find_diff(6);
    set_decay_time(4000);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
