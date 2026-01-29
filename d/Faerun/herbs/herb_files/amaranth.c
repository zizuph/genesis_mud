/*
 * Amaranth - This herb heals health
 * /d/Faerun/herbs/herb_files/amaranth.c
 * Finwe, Jan 2009
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb";

void
create_herb()
{
    set_name("flowers");
    add_name("flower");
    set_adj(({"cluster", "blood-red"}));
    set_herb_name("amaranth");
    set_short("cluster of blood-red flowers");
    set_pshort("clusters of blood-red flowers");
    set_ingest_verb("eat");
    set_unid_long("This is a cluster of blood-red flowers.\n");
    set_id_long("This is a cluster of flowers from an Amaranth. The plant is a tall annual herb with a stout, erect stalk. The leaves are dull green with purple-red spots. Deeply veined on the underside, they are oval and taper to a point. Dense clusters of small, crimson to blood-red flowers appear in long, upright spikes. The flowers are used to heal wounds.\n");
    set_herb_value(100);
    set_id_diff(75);
    set_find_diff(8);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",110);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
