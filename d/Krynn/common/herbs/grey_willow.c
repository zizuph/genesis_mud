/* Willow by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("bark");
    add_name(({"willow"}));
    add_adj(({"willow"}));
    set_adj("grey");
    set_herb_name("grey willow");
    set_short("grey bark");
    set_pshort("grey barks");
    set_pname(({"barks", "herbs", }));
    set_ingest_verb("chew");
    set_unid_long(BSN("This is a grey bark. It was probably " +
        "picked from a shrub or tree near a riverbank or open plains."));
    set_id_long(BSN("This is the bark of willow, a shrub or tree found " +
        "in temperate open areas and riverbanks. Willow (Salix spp.) " + 
        "typically has long slender leaves, and grows from 1 to 20 " +
        "meters tall. It flowers early in spring, bearing catkins. " +
        "Willow bark is rumoured to have some medicinal value when chewed."));
    set_herb_value(214);
    set_id_diff(20);
    set_find_diff(4);
    set_effect(HERB_CURING,"mana",26);
    set_decay_time(9000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
