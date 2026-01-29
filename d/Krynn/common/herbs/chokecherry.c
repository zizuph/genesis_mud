/* Chokecherry by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj(({"black", "shiny"}));
    set_herb_name("chokecherry");
    set_short("black shiny berry");
    set_pshort("black shiny berries");
    set_pname(({"berries", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a black shiny berry. It was probably " +
        "picked from a tall shrub in a forest."));
    set_id_long(BSN("This is the berry of chokecherry, a shrub found " +
        "in temperate forests. Chokecherry (Prunus virginiana) is a tall " + 
        "shrub that grows to 4 or 5 meters high. The berries are found in " +
        "clusters. They are highly edible, and can give some relief " +
        "from tiredness. Chokecherries are used to make wine.")); 
    set_herb_value(36);
    set_id_diff(13);
    set_find_diff(5);
    set_effect(HERB_HEALING,"fatigue",3);
    set_decay_time(6700);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
