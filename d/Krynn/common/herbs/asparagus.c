/* Asparagus by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("stalk");
    set_adj(({"green", "upright"}));
    set_herb_name("asparagus");
    set_short("upright green stalk");
    set_pshort("upright green stalks");
    set_pname(({"stalks", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an upright green stalk. It was probably " +
        "picked from somewhere near a source of water."));
    set_id_long(BSN("This is the stalk of asparagus, an herb found " +
        "in temperate areas near water. Asparagus (Asparagus spp.) is " +
        "a common spring time vegetable, the stalks being high in vitamins. " +
        "In the late summer, it has feathery leaves and juicy berries. " +
        "This herb is very edible, and good for the mind and body."));
    set_herb_value(124);
    set_id_diff(17);
    set_find_diff(4);
    set_effect(HERB_HEALING,"fatigue",5);
    add_effect(HERB_HEALING,"mana",5);
    set_decay_time(7000);
    set_dryable();
    set_amount(8);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
