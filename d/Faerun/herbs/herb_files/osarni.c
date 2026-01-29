/* 
 * osarni - Heals fatigue
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
    set_name("bark");
    set_adj(({"large", "prickly"}));
    set_herb_name("osarni");
    set_short("large prickly bark");
    set_pshort("large prickly barks");
    set_ingest_verb("eat");
    set_unid_long("This is a large prickly bark.\n");
    set_id_long("This is a large prickly bark from the Osarni plant. It is from a vine that grows in the Underdark across walls. The bark is grey colored and feels rough and rumoured to make you less tired.\n");
    set_herb_value(( 4 * 5) + (5 * 5)/4 );
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"fatigue",5);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
