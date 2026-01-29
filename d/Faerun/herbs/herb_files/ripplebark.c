/* 
 * ripplebark - Minor health
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
    set_name("fungus");
    set_adj(({"smelly", "brown"}));
    set_herb_name("ripplebark");
    set_short("smelly brown fungus");
    set_pshort("smelly brown fungi");
    set_ingest_verb("eat");
    set_unid_long("This is a smelly brown fungus.\n");
    set_id_long("This fungus is known as Ripplebark. It is shelf-like shaped, resembles a mass of rotting flesh and stinks. Found in the Underdark, it is surprisingly edible and said to do minor healing.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4 );
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
