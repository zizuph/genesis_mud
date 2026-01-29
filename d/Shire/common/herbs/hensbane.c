/*
 * hens_bane.c
 * cleanses poisons.
 * Finwe, March 2003
 */

#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb.c";

#define EFFECT "/d/Shire/common/herbs/hensbaneef"


create_herb()
{
    set_name("hensbane");
    add_name("flower");
    set_adj(({"pale","yellow"}));
    set_short("pale yellow flower");
    set_pshort("pale yellow flowers");
    set_herb_name("hensbane");
    set_id_long("This is a flower of the Hensbane plant. It has large, " +
        "thick, soft woolly leaves, and thick stalks and medium site in " +
        "height. The plant has hollow pale yellow flowers at the " +
        "top of the stalk and found in temperate grasslands and meadows. " +
        "It is said to reduce poisons when eaten.\n");
    set_unid_long("This is a pale yellow flower\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(4);
//    set_effect(HERB_CURING, "all", 50);
    set_effect(HERB_SPECIAL);

    set_decay_time(2500);
    set_herb_value(250);
    set_dryable();
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }

void
special_effect()
{
    object eff;
    eff = clone_object(EFFECT);
    eff->move(this_player());
}
