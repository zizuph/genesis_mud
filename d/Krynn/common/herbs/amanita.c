/* Amanita by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("mushroom");
    set_adj(({"snow", "white"}));
    add_adj("snow-white");
    set_herb_name("amanita");
    set_short("snow-white mushroom");
    set_pshort("snow-white mushrooms");
    set_pname(({"mushrooms", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a snow-white mushroom. It was " +
        "probably picked from a forest floor."));
    set_id_long(BSN("This is Amanita, a deadly mushroom found " +
        "in temperate forests. Amanita (Amanita virosa) is a " + 
        "fungus that grows to about 20 cm high. Members of this genus " +
        "are characterized by a snow-white cap, a ringed stalk and a " +
        "cup around its base. This fungus often grows in 'fairy rings'. " +
        "This mushroom has the common name, 'Death Angel', strongly " +
        "hinting at its lethal nature."));
    set_effect(HERB_POISONING,"herb",65);
    set_poison_file(KRPOISON + "amanitap");
    add_effect(HERB_HEALING,"hp",-200);
    add_effect(HERB_HEALING,"mana",-500);
    set_herb_value(60);
    set_id_diff(25);
    set_find_diff(8);
    set_decay_time(2000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
