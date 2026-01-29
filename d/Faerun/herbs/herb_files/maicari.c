/* 
 * maicari - Poisonous
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
    set_name("bulb");
    set_adj(({"small", "dry"}));
    set_herb_name("maicari");
    set_short("small dry bulb");
    set_pshort("small dry bulbs");
    set_ingest_verb("eat");
    set_unid_long("This is a small dry bulb.\n");
    set_id_long("This is a small dry bulb from the Maicari plant. It is slightly violet colored and grows in the Underdark in groups. The bulb feels bumpy and unhealthy.\n");
    set_herb_value(( 4 * 5) + (5 * 5)/4 );
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_POISONING,"herb",25);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
