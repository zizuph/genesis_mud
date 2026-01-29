/* Bull Kelp by Teth, March 2,96 */
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
    set_herb_name("bull kelp");
    set_short("sinuous green-brown alga");
    set_pshort("sinuous green-brown algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a sinuous green-brown alga. It was probably " +
        "picked far offshore in the ocean depths."));
    set_id_long(BSN("This is bull kelp, a sinuous green-brown alga found " +
        "far offshore in the ocean depths. Bull kelp (Neriocystis spp.) " +
        "is a green-brown colour, and has a single long stipe which " +
        "enlarges to an elongate float and terminal bulb, from which the " +
        "blades emerge. It is used as a foodstuff, and is also said to " +
        "make one feel less fatigued."));
    set_herb_value(625);
    set_id_diff(30);
    set_find_diff(9);
    set_effect(HERB_HEALING,"fatigue",35);
    set_decay_time(7500);
    set_dryable();
    set_amount(40);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
