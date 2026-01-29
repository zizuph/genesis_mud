/* 
 * sussur - Enhances magic
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
    set_name("root");
    set_adj(({"long", "gnarled"}));
    set_herb_name("sussur");
    set_short("long gnarled root");
    set_pshort("long gnarled roots");
    set_ingest_verb("eat");
    set_unid_long("This is a long gnarled root.\n");
    //set_id_long("This is a root from the Sussur tree. It grows in the Underdark in areas of strong faerzress. The plant grows tree-like and has few leaves but has many gnarled aerial roots. When eaten, it is said to transfer its magical abiliies.\n");
    set_id_long("This is a root from the Sussur tree. It grows in the Underdark in areas of strong faerzress. The plant grows tree-like and has few leaves but has many gnarled aerial roots.\n");
    set_herb_value(( 4 * 35) + (35 * 35)/4 );
    
    set_id_diff(40);
    set_find_diff(9);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    // Emh, no. 35 MR for eating a herb that also stacks
    // the effect? Not on my watch. - Nerull.
    //set_effect(HERB_ENHANCING,"magic",35);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
