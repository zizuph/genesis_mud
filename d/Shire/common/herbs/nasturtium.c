/*
 * Nasturtium leaf
 * Finwe, March 2003
 */

#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb.c";

create_herb()
{
    set_name("nasturtium");
    add_name("leaf");
    set_adj(({"round","veined"}));
    set_short("round veined leaf");
    set_pshort("round veined leaves");
    set_herb_name("nasturtium");
    set_id_long("This is a leaf of the common Nasturtium plant. It is " +
        "a hardy, trailing plant covered with round green leaves that " +
        "are heavily veined. The plant is often covered with showy " +
        "red, yellow, or orange flowers in the summer time. The leaves " +
        "are edible and have slight healing properties.\n");
    set_unid_long("This is a round veined leaf.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(1);
    set_effect(HERB_HEALING,"hp",5);
    set_decay_time(2000);
    set_herb_value(350);
    set_dryable();
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
