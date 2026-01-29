/* 
 * drace - this herb grows in dry mountain or desert regions
 * of Faerun ONLY. By itself, it has no non-culinary properties, but
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
    set_adj(({"dark", "blue"}));
    set_herb_name("drace");
    set_short("dark blue leaf");
    set_pshort("dark blue leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a dark blue leaf commonly found on shrubs
    in the drier regions of Faerun. \n");
    set_id_long("This dark blue leaf is known as drace, plucked from the
    the bittergar bush, a small, thistle-like shrub that grows in the
    mountains and deserts of Faerun. It is known to improve the flavor
    of food, but is also sometimes sought by alchemists as an ingredient
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
