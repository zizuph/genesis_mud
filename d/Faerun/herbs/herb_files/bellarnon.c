/* 
 * bellarnon - Heals Fatigue
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
    set_name("bean");
    set_adj(({"big", "rotting"}));
    set_herb_name("bellarnon");
    set_short("big rotting bean");
    set_pshort("big rotting beans");
    set_ingest_verb("eat");
    set_unid_long("This is a big rotting bean.\n");
    set_id_long("This is a big rotting bean from the Bellarnon plant. The plant is a shrub that grows in the Underdark. The bean is slightly green colored and feels rough and bumpy.\n");
    set_herb_value(( 4 * 5) + (5 * 5)/4 );
    set_id_diff(30);
    set_find_diff(3);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"fatigue",5);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
