/* Saskatoon by Teth, March 3,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj(({"blue", "little"}));
    set_herb_name("saskatoon");
    set_short("little blue berry");
    set_pshort("little blue berries");
    set_pname(({"berries", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a little blue berry. It was probably " +
        "picked from a shrub in a forest, or on a prairie."));
    set_id_long(BSN("This is a saskatoon, a berry from a shrub found " +
        "in temperate forests and plains. Saskatoon (Amelanchier " +
        "alnifolia) is a medium sized shrub, growing from 50 cm to 3m " + 
        "tall. Its berries are very similar in appearance to those of " +
        "blueberry, though they are only distantly related. The berries " +
        "are useful for small healing and curing tiredness."));
    set_herb_value(43);
    set_id_diff(16);
    set_find_diff(3);
    set_effect(HERB_HEALING,"fatigue",2);
    add_effect(HERB_HEALING,"hp",1);
    set_decay_time(10000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
