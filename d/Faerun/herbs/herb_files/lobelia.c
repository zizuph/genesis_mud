/* 
 * lobelia - Cures Poison
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
    set_name("flower");
    set_adj(({"pale", "lavender"}));
    set_herb_name("lobelia");
    set_short("pale lavender flower");
    set_pshort("pale lavender flowers");
    set_ingest_verb("eat");
    set_unid_long("This is a pale lavender flower.\n");
    set_id_long("This pale lavender flower is known as Lobelia. The plant is short and covered with trumpet shaped flowers. It grows in grasslands and rumored to heal poisons.\n");
    set_herb_value(( 4 * 30) + (30 * 30)/4 );
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_CURING,"all",30);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
