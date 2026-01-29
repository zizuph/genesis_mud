/* Sphagnum moss by Teth, Feb.16,96 */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("moss");
    set_adj(({"greenish", "brown"}));
    set_herb_name("sphagnum");
    set_short("greenish brown moss");
    set_pshort("greenish brown mosses");
    set_pname(({"mosses", "herbs", }));
    set_ingest_verb("embrue");
    set_unid_long(BSN("This is a greenish brown moss. It was most " +
        "likely found in a bog, near acidic waters."));
    set_id_long(BSN("This is sphagnum, a greenish brown moss found " +
        "in bogs. Since it is so absorptive and acidic, adventurers have " +
        "found that if they embrue the moss with their blood, the moss " +
        "would cleanse and heal their wounds, offering some relief."));
    set_herb_value(1018);
    set_id_diff(15);
    set_find_diff(2);
    set_effect(HERB_HEALING,"hp",48);
    set_decay_time(10000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
