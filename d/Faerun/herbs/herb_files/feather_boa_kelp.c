/* 
 * feather boa kelp - Heals fatigue slightly
 * Finwe, January 2009
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
    set_name("kelp");
    add_name("seaweed");
    set_adj(({"dark-brown", "feathery"}));
    set_herb_name("feather boa kelp");
    set_short("dark-brown feathery kelp");
    set_pshort("dark-brown feathery kelps");
    set_ingest_verb("eat");
    set_unid_long("This is a strand of dark-brown feathery kelp.\n");
    set_id_long("This is a strand of Feather Boa kelp. It grows in the sea and was washed up onto a seashore. The strand has many small brown leaves resembling a feather boa. Locals believe eating the kelp makes them less tired.\n");
    set_herb_value(350);
    set_id_diff(30);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"fatigue",25);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
