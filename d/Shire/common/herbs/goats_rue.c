/*
 * goats_rue.c
 * Cures poison. A modified version of catnip.c, which was a 
 * modified version of tuo.
 * 
 * Finwe, March 2003
 */

#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb.c";

void create_herb()
{
    set_name("flower");
    set_adj(({"pale","whitish-blue"}));
    set_short("pale whitish-blue flower");
    set_pshort("pale whitish-blue flowers");
    set_herb_name("goats rue");
    set_id_long("This root is the flower of Goats Rue. Its pale " +
        "whitish-blue flowers hang down in spikes from tall hollow " +
        "stems. The flowers are believed to cure poison when eaten, " +
        "and the plant grows in temperate forests.\n");
    set_unid_long("This is a pale whitish-blue flower\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(4);
    set_effect(HERB_CURING, "all", 10);
    set_decay_time(2500);
    set_herb_value(864);
    set_dryable();
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
