/* Vallenwood Blossom by Arman Feb 2016 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("blossom");
    add_name("_sohm_vallenwood_blossom");
    set_adj(({"lovely", "white"}));
    set_herb_name("vallenwood blossom");
    set_short("lovely white blossom");
    set_pshort("lovely white blossoms");
    set_pname(({"blossoms", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long("This is a lovely white flower blossom with orange pollen at its core. " +
        "This flower blossom looks almost like a small hand, with five small tepals, which " +
        "when fully outstretched span roughly twelve inches.\n");
    set_id_long("This is a vallenwood blossom (lignacampi floreant), a rare beautiful " +
        "white flower that grow only in the upper reaches of the mighty vallenwoods of Krynn. " +
        "When eaten these blossoms refresh a weary soul.\n");
    set_herb_value(80);
    set_id_diff(9);
    set_find_diff(6);
    set_effect(HERB_HEALING,"fatigue",4);
    set_decay_time(4000);
    set_dryable();
    set_amount(10);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
