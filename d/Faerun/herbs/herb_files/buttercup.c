/* 
 * Buttercup - Poisonous.
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
    set_name("flower");
    set_adj(({"small", "yellow"}));
    set_herb_name("buttercup");
    set_short("small yellow flower");
    set_pshort("small yellow flowers");
    set_ingest_verb("eat");
    set_unid_long("This is a small yellow flower.\n");
    set_id_long("This small yellow flower is known as a Buttercup. It has five, small yellow petals that surround a yellow center. It is very common and often carpets meadows.\n");
    set_herb_value(( 4 * 15) + (15 * 15)/4 );
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_POISONING,"hp",15);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
