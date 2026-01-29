/* 
 * adildra - Minor mana
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
    set_name("grass");
    set_adj(({"ordinary", "delicate"}));
    set_herb_name("adildra");
    set_short("ordinary delicate grass");
    set_pshort("ordinary delicate grasses");
    set_ingest_verb("eat");
    set_unid_long("This is a ordinary delicate grass.\n");
    set_id_long("This is a ordinary delicate blade of grass known as Adildra. " +
        "It is slightly white and green colored, and grows in the Underdark " +
        "in small clumps.\n");
    set_herb_value(( 4 * 5) + (5 * 5)/4 );
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"mana",5);
}

string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
