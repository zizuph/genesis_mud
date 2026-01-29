/*
 * Blackroot, heals
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
    set_name("blackroot");
    add_name("root");
    set_adj(({"black","fiberous"}));
    set_short("black fiberous root");
    set_pshort("black fiberous roots");
    set_herb_name("blackroot");
    set_id_long("This root is from a tall plant named Blackroot. The " +
        "plant has small, bell-shaped violet flowers and complex roots " +
        "that are black on the outside and white on the inside. " +
        "Blackroot's roots can be applied to fresh wounds in order to " +
        "promote quick healing. The plant grows in temperate areas.\n");
    set_unid_long("This is a fiberous black root\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(2);
    set_effect(HERB_HEALING,"hp",2);
    set_decay_time(2500);
    set_herb_value(427);
    set_dryable();
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
