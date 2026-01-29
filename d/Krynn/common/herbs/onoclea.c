/* Onoclea by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("fern");
    set_adj(({"simple", "delicate"}));
    set_herb_name("onoclea");
    set_short("simple delicate fern");
    set_pshort("simple delicate ferns");
    set_pname(({"ferns", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a simple delicate fern. It was probably " +
        "picked near a sunny streamside or moist prairie."));
    set_id_long(BSN("This is the fern called onoclea, an herb found " +
        "in temperate areas near water. Onoclea (Onoclea sensibilis) " +
        "is also called the sensitive fern. It has green simple fronds " +
        "which aren't highly dissected, unlike most other ferns. " +
        "The fern is edible, and is said to aid the quailing heart."));
    set_herb_value(356);
    set_id_diff(35);
    set_find_diff(6);
    set_effect(HERB_ENHANCING,"dis",32);
    add_effect(HERB_HEALING,"fatigue",1);
    set_decay_time(4700);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
