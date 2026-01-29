/* 
 * dead man's fingers - Does minor healing
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
    set_name("seaweed");
    set_adj(({"feathery", "green"}));
    set_herb_name("dead man's fingers");
    set_short("feathery green seaweed");
    set_pshort("feathery green seaweeds");
    set_ingest_verb("eat");
    set_unid_long("This is a piece of feathery green seaweed.\n");
    set_id_long("This is a piece of feathery green seaweed known as " +
        "Dead Man's Fingers. The seaweed has meany branches that resemble " +
        "feathers. It is found growing in the seas and often washed " +
        "up on the coast. Some eat it hoping the seaweed will heal them.\n");
    set_herb_value(( 4 * 10) + (10 * 10)/4 );
    set_id_diff(30);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",10);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
