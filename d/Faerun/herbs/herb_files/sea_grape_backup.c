/* Sea Grape - sees hidden and invisibles, and restricted to only Faerun
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

#define EFFECT "/d/Faerun/herbs/herb_files/sea_grapeef"


void
create_herb()
{
    set_name("berry");
    set_adj(({"small", "green"}));
    set_herb_name("sea grape");
    set_short("small green berry");
    set_pshort("small green berries");
    set_ingest_verb("eat");
    set_unid_long("This is a small green berry.\n");
    set_id_long("This is a Sea Grape berry. It comes from a small shrub covered with small, round leaves. The berry is small and light green and found growing along seashores.\n");
    set_herb_value(( 4 * 40) + (40 * 40)/4 );
    set_id_diff(45);
    set_find_diff(9);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_SPECIAL,"all",40);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }

void
special_effect()
{
    object eff;
    eff = clone_object(EFFECT);
    eff->move(this_player());
}
