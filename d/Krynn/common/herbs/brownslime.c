/* Brown Slime by Teth, April 5,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"brown", "slimy"}));
    set_herb_name("brown slime");
    set_short("slimy brown alga");
    set_pshort("slimy brown algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("chew");
    set_unid_long(BSN("This is a slimy brown alga. It was probably " +
        "found in a dark wet place or a sewer."));
    set_id_long(BSN("This is a slimy brown alga, an herb found " +
        "in dark wet places, like sewers. Brown slime enjoys nutrient " +
        "rich environments, where it grows in proliferation. Unlike most " +
        "algae and fungi you'd expect to find in these places, this one is " +
        "rumoured to have a beneficial effect when chewed."));
    set_herb_value(76);
    set_id_diff(8);
    set_find_diff(5);
    set_effect(HERB_HEALING,"hp",10);
    set_decay_time(2000);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
