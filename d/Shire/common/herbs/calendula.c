/*
 * Calendula
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
    set_name("calendula");
    add_name("flower");
    set_adj(({"delicate","yellow"}));
    set_short("delicate yellow flower");
    set_pshort("delicate yellow flowers");
    set_herb_name("calendula");
    set_id_long("This is the flower from the common Calendula. It is a " +
        "common plant and covered with long green leaves. The plant is " +
        "hardy and grows in moist climates. The daisy-like flowers are " +
        "prized for their healing abilities and often dried and used " +
        "in poultices placed on wounds.\n");
    set_unid_long("This is a delicate yellow flower.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(1);
    set_effect(HERB_HEALING,"hp",3);
    set_decay_time(2000);
    set_herb_value(350);
    set_dryable();
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
