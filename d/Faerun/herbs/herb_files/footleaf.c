/*
 * Footleaf - Eases fatigue in player
 * Finwe, 
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
    set_adj(({"thick", "fleshy"}));
    set_herb_name("footleaf");
    set_short("thick fleshy leaf");
    set_pshort("thick fleshy leaves");
    set_ingest_verb("eat");
    set_unid_long("This thick fleshy leaf is is dark green and covered with soft hairs.\n");
    set_id_long("This is a leaf of the Footleaf plant. It is thick and fleshy and covered with soft hairs. The leaf is dark green and when eaten is rumored to ease fatigue.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4 );
    set_id_diff(30);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"fatigue",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
