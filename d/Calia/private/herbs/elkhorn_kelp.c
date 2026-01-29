/* Elkhorn Kelp by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"sinuous", "green-brown"}));
    set_herb_name("elkhorn kelp");
    set_short("sinuous green-brown alga");
    set_pshort("sinuous green-brown algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a sinuous green-brown alga. It was probably " +
        "picked far offshore in the ocean depths."));
    set_id_long(BSN("This is elkhorn kelp, a sinuous green-brown alga found " +
        "far offshore in the ocean depths. Elkhorn kelp (Pelagophycus " +
        "porra) is a green-brown colour, and has a single long stipe which " +
        "enlarges to a large float, from which the large blades grow. " +
        "It is used as a foodstuff, and is also said to " +
        "make one feel less fatigued."));
    set_herb_value(30);
    set_id_diff(31);
    set_find_diff(7);
    set_effect(HERB_HEALING,"fatigue",6);
    set_decay_time(7500);
    set_dryable();
    set_amount(15);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
