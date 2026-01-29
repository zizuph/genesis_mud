/* 
 * alarvaun - this herb grows in wet marshes and is unique
 * to southern Faerun ONLY. By itself, it has no properties, but
 * will be used as an ingredient in Spellslayer wine, a concoction
 * that disables a character's ability to cast spells. This
 * can be used for the future implementation of Spellslayer wine
 * that may be useful in some quests, or by mages who need to
 * enter parts of Faerun dangerous for mages with active magic
 * due to lingering effects of the Spellplague.
 *
 * Twire, September 2016
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
    set_name("leaves");
    set_adj(({"green", "waxy"}));
    set_herb_name("alarvaun");
    set_short("waxy green leaf");
    set_pshort("waxy green leaves leaves");
    set_ingest_verb("eat");
    set_unid_long("This waxy green leaf has been stripped from a vine
   that commonly grows in certain wet, shady regions of Faerun. \n");
    set_id_long("This is alarvaun, the waxy leaf carefully stripped from
    the vaundyr vine, a plant that grows in abundance in wet, shady areas
    in southern Faerun. It is sometimes sought by alchemists as an ingredient
    in Spellslayer wine.\n");
    set_herb_value(400);
    set_id_diff(15);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
