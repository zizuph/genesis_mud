/* 
 * red algae - Provides minor health
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
    set_name("alga");
    set_adj(({"red", "iridescent"}));
    set_herb_name("red alga");
    set_short("red iridescent alga");
    set_pshort("red iridescent algae");
    set_ingest_verb("eat");
    set_unid_long("This is a blade of red iridescent alga.\n");
    set_id_long("This is a blade from the Red Alga. It is reddish colored and when moved, has a iridescent color. The blade of the plant is broad and flat with ruffled margins, and locals believe it will heal them when eaten.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4 );
    set_id_diff(30);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
