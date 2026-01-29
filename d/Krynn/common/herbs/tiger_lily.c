/* Tiger Lily by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"black-speckled", "orange"}));
    set_herb_name("tiger lily");
    set_short("black-speckled orange flower");
    set_pshort("black-speckled orange flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an black-speckled orange flower. It was " +
        "probably picked from a narrow-leaved herb in a sunny prairie."));
    set_id_long(BSN("This is a flower of tiger lily, a lily found " +
        "in temperate plains. Tiger lily (Lilium philadelphicum) is a " + 
        "herb that grows to about 60 cm high. The flower is orange " +
        "and speckled with black, hence the name. It is said that eating " +
        "any part of most lilies results in laziness and weariness."));
    set_effect(HERB_POISONING,"fatigue",30);
    set_herb_value(30);
    set_id_diff(30);
    set_find_diff(6);
    set_decay_time(3000);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
