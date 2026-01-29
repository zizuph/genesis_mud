/* 
 * carolden - minor health
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
    set_name("fungus");
    set_adj(({"narrow", "dry"}));
    set_herb_name("carolden");
    set_short("narrow dry fungus");
    set_pshort("narrow dry fungi");
    set_ingest_verb("eat");
    set_unid_long("This is a narrow dry fungus.\n");
    set_id_long("This is a narrow dry fungus called Carolden. It is deep blue and white colored,  and grows on ledges in the Underdark. The fungus feels rough and its edges serrated.\n");
    set_herb_value(55);
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",1);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
