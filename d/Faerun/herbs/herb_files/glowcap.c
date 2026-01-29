/* 
 * glowcap - Raises INT.
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
    set_adj(({"glowing", "blue"}));
    set_herb_name("glowcap");
    set_short("glowing blue mushroom");
    set_pshort("glowing blue mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a glowing blue mushroom.\n");
    set_id_long("This glowing blue mushroom is known in the Underdark as " +
        "Glowcap. The mushroom grows in small groups and in regions of " +
        "high faerzress and absorbs the surrounding magics.\n");
    set_herb_value(( 4 * 58) + (58 * 58)/4 );
    set_id_diff(30);
    set_find_diff(3);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_ENHANCING,"int",23);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
