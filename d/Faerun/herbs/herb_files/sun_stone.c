/* 
 * sun stone - Underdark herb - Minor health
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
    set_name("mushroom");
    add_name("mushrooms");
    set_adj(({"cluster of", "orange"}));
    set_herb_name("sun stone");
    set_short("cluster of orange mushrooms");
    set_pshort("clusters of orange mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a cluster of orange mushrooms.\n");
    set_id_long("This is a cluster of orange mushrooms known to travellers as Sun Stones. They are round and orange colored, resembling the sun. They are found in the Underdark and gathered by brave people who travel there. It is said the herb will heal your wounds.\n");
    set_herb_value(( 4 * 10) + (10 * 10)/4 );
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",10);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
