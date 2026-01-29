/* Hawthorn by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj("red");
    set_herb_name("hawthorn");
    set_short("red berry");
    set_pshort("red berries");
    set_pname(({"berries", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a red berry. It was probably " +
        "picked from a shrub near a riverbank or open plains."));
    set_id_long(BSN("This is the berry of hawthorn, a shrub found " +
        "in temperate open areas and riverbanks. Hawthorn (Craetaegus " + 
        "chrysocarpa) is a shrub that has long thorns, reaching 10 cm " +
        "in length. The shrub itself grows to a height of 3m. The berries " +
        "are edible, giving a hungry adventurer some relief."));
    set_herb_value(36);
    set_id_diff(6);
    set_find_diff(3);
    set_effect(HERB_HEALING,"fatigue",3);
    set_decay_time(10000);
    set_dryable();
    set_amount(2);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
