/* 
 * bloodfruit - Minor Healing
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
    set_name("fruit");
    set_adj(({"bitter", "red"}));
    set_herb_name("bloodfruit");
    set_short("bitter red fruit");
    set_pshort("bitter red fruits");
    set_ingest_verb("eat");
    set_unid_long("This is a bitter red fruit.\n");
    set_id_long("This fruit is from the Bloodfruit tree in the Underdark. The fruit is produced every 3-4 years and is small and bitter looking. It is said to do minor healing.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4 );
    set_id_diff(30);
    set_find_diff(3);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
