/* 
 * lorea - Does nothing
 * Finwe, February 2009
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
    set_name("fern");
    set_adj(({"narrow", "rotting "}));
    set_herb_name("lorea");
    set_short("narrow rotting fern");
    set_pshort("narrow rotting ferns");
    set_ingest_verb("eat");
    set_unid_long("This is a narrow rotting fern.\n");
    set_id_long("This is a narrow rotting fern named Lorea. The fronds are slightly purple colored and comes from the Underdark. The fern feels fuzzy and smells rotten.\n");
    set_herb_value(77);
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
