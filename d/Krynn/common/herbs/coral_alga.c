/* Coralline Red Alga by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"gritty", "segmented"}));
    set_herb_name("coralline red alga");
    set_short("gritty segmented alga");
    set_pshort("gritty segmented algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a gritty segmented alga. It was probably " +
        "picked nearshore or in the intertidal zone."));
    set_id_long(BSN("This is a gritty segmented alga, an herb found " +
        "in nearshore oceans and intertidal areas. Coralline red alga " +
        "(Corallina spp.) is a reddish or pinkish brown colour, with " +
        "whitish tips to the branches. It contains deposits of calcium " +
        "carbonates (or so the mages say), making it gritty and rough-" +
        "textured. Eating it would probably hurt you, considering the " +
        "coarse feel of the herb."));
    set_herb_value(26);
    set_id_diff(15);
    set_find_diff(3);
    set_effect(HERB_HEALING,"hp",-20);
    set_decay_time(10000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
