/* 
 * ranindir - Minor fatigue
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
    set_adj(({"rough", "black"}));
    set_herb_name("ranindir");
    set_short("rough black bean");
    set_pshort("rough black beans");
    set_ingest_verb("eat");
    set_unid_long("This is a rough black bean.\n");
    set_id_long("This is a rough black bean from the Ranindir plant deep in the Underdark. The bean is thumb-size and covered with small bumps.\n");
    set_herb_value(( 4 * 2) + (2 * 2)/4 );
    set_id_diff(30);
    set_find_diff(3);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"fatigue",2);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
