/*
 * Tansy
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
    set_name("tansy");
    add_name("flower");
    set_adj(({"bright","yellow"}));
    set_short("bright yellow flower");
    set_herb_name("tansy");
    set_id_long("This is the flower of the popular Tansy plant. Its " +
        "flowers are bright yellow and found growing in moist areas. " +
        "The plants are small with serrated green leaves. The plant " +
        "has been know to be fatal, though it's not very poisonous. \n");
    set_unid_long("This is a bright yellow flower.\n");
    set_ingest_verb("eat");
    set_id_diff(23);
    set_find_diff(1);
    set_effect(HERB_POISONING, "tansy", 15);
    set_poison_damage(({POISON_HP, 20, POISON_FATIGUE, 20, POISON_MANA, 20,
      POISON_STAT, SS_CON}));
    set_decay_time(1800);
    set_herb_value(350);
    set_dryable();

}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
