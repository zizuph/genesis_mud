/* Lavendar - Is a common herb and has light healing properties.
 * Finwe, January 17, 2009
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
    set_adj(({"handful of", "gray-green"}));
    set_herb_name("lavendar");
    set_short("handful of gray-green leaves");
    set_pshort("handfuls of gray-green leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a handful of gray-green leaves. The leaves are small and narrow and very fragrant.\n");
    set_id_long("This is handful of Lavendar leaves. The leaves are small and narrow and covered with a silvery down. They come from a heavily branched bush that grows to be about knee high. Lavendar is prized for its oils and is even known to have some healing properties. \n");
    set_herb_value(( 4 * 10) + (10 * 10)/4 );
    set_id_diff(15);
    set_find_diff(3);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",10);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
