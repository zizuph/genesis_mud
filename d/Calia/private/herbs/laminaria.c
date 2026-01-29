/* Laminaria by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"green", "slimy"}));
    set_herb_name("laminaria");
    set_short("slimy green alga");
    set_pshort("slimy green algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a slimy green alga. It was probably " +
        "picked offshore in somewhat deep waters."));
    set_id_long(BSN("This is a slimy green alga, an herb found " +
        "in offshore in somewhat deep waters. Laminaria (Laminaria spp.) " +
        "is a fairly large algae, rooting on rocks with a specialized " +
        "structure called a holdfast. It has several large green blades " +
        "which extend upwards, floating in the water column. This alga " +
        "has no known effect."));
    set_herb_value(14);
    set_id_diff(30);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
