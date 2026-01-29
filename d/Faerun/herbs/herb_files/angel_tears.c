/* 
 * angel tears - Underdark herb. Provides minimum healing
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
    set_name("lichen");
    set_adj(({"pale", "white"}));
    set_herb_name("angel tears");
    set_short("pale white lichen");
    set_pshort("pale white lichens");
    set_ingest_verb("eat");
    set_unid_long("This is a piece of pale white lichen.\n");
    set_id_long("This piece of pale white lichen is known as Angel Tears. Travellers to the Underdark find it growing in deep cracks. The lichen has small nodules on it and is said to heal.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4);
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",10);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
