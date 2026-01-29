/* Green Slime by Teth, April 5,96 */
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
    set_herb_name("green slime");
    set_short("slimy green alga");
    set_pshort("slimy green algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a slimy green alga. It was probably " +
        "found in a dark wet place or a sewer."));
    set_id_long(BSN("This is a slimy green alga, an herb found " +
        "in dark wet places, like sewers. Green slime enjoys nutrient " +
        "rich environments, where it grows in proliferation. This particular "+
        "alga is coloured a sickly pale green. Like most algae and fungi "+
        "you'd expect to find in these places, this one is rumoured to have "+
        "a harmful effect when eaten."));
    set_herb_value(20);
    set_id_diff(3);
    set_find_diff(3);
    set_effect(HERB_HEALING,"hp",-10);
    add_effect(HERB_HEALING,"fatigue",-20);
    set_decay_time(2000);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
