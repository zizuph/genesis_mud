/* 
 * angelica - Cures all poisons
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
    set_adj(({"long", "triangular"}));
    set_herb_name("angelica");
    set_short("long triangular leaf");
    set_pshort("long triangular leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a long trangular shaped leaf.\n");
    set_id_long("This long trangular shaped leaf is from the Angelica plant. It grows to about 4 feet tall. Its tall stems that are purple-green, hollow, and divided. It often blooms twice a year with a spray of flowers. Common folklore holds that if you eat the leaf, it will cure most poisons.\n");
    set_herb_value(( 4 * 75) + (75 * 75)/4 );
    set_id_diff(20);
    set_find_diff(5);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_CURING,"all",75);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
