/* Fiddlehead by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("frond");
    set_adj(({"green", "unfurling"}));
    set_herb_name("fiddlehead");
    set_short("unfurling green frond");
    set_pshort("unfurling green fronds");
    set_pname("fiddleheads");
    add_pname(({"fronds", "herbs"}));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an unfurling green frond. It was probably " +
        "picked from a sunny forest."));
    set_id_long(BSN("This is the developing frond of a fern called a " +
        "fiddlehead. It is a rich green colour and is found in temperate " +
        "sunny forest. Fiddleheads (Matteucia spp.) are so named because " +
        "of the structural resemblance to the furled wood at the tip of " +
        "a violin. They are high in minerals and vitamins. " +
        "This herb is very edible, and good for the mind and body."));
    set_herb_value(142);
    set_id_diff(5);
    set_find_diff(4);
    set_effect(HERB_HEALING,"hp",20);
    add_effect(HERB_HEALING,"mana",5);
    set_decay_time(2500);
    set_amount(4);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
