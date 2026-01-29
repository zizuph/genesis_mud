/* Beach Plum by Teth, March 1,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("fruit");
    set_adj(({"dry", "purplish"}));
    set_herb_name("beach plum");
    set_short("dry purplish fruit");
    set_pshort("dry purplish fruits");
    set_pname(({"fruits", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a dry purplish fruit. It was probably " +
        "picked off a scrubby shrub on an ocean beach sand dune."));
    set_id_long(BSN("This is a beach plum, a dry purplish fruit found " +
        "on sand dunes near ocean beaches. Beach plum (Prunus sp.) is a " +
        "scrubby shrub that grows to about 1 meter high. The shrub has " + 
        "sweet-scented blossoms, white in colour. The fruit of the shrub " +
        "is said to refresh and feed a weary soul."));
    set_herb_value(54);
    set_id_diff(18);
    set_find_diff(4);
    set_effect(HERB_HEALING,"fatigue",3);
    set_decay_time(6000);
    set_dryable();
    set_amount(5);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }

