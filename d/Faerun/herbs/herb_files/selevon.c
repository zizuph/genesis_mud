/* 
 * selevon - Increases Wisdom
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
    set_name("leaf");
    set_adj(({"large", "blue"}));
    set_herb_name("selevon");
    set_short("large blue leaf");
    set_pshort("large blue leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a large blue leaf.\n");
    set_id_long("This leaf is from the Selevon plant. It grows in clumps and has blue and white leaves. They are spade shaped and have a light dusting of hair across each leaf.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4 );
    set_id_diff(30);
    set_find_diff(5);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_ENHANCING,"wis",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
