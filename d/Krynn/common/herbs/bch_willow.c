/* Beach Willow by Teth, March 1,96 */
/* Added name 'willow', Arman 2017 */
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
    set_adj(({"grey", "gnarled"}));
    set_herb_name("beach willow");
    set_short("grey gnarled bark");
    set_pshort("grey gnarled barks");
    set_pname(({"barks", "herbs", }));
    set_ingest_verb("chew");
    set_unid_long(BSN("This is a grey gnarled bark. It was probably " +
        "picked from a shrub near a beach dune."));
    set_id_long(BSN("This is the bark of beach willow, a shrub found " +
        "on ocean beach dunes. Beach willow (Salix spp.) " + 
        "has short slender serrated leaves, and grows from 1 to 2 " +
        "meters tall. It flowers early in spring, bearing catkins. " +
        "Beach willow is rumoured to have some medicinal value when chewed."));
    set_herb_value(320);
    set_id_diff(32);
    set_find_diff(5);
    set_effect(HERB_HEALING,"mana",10);
    add_effect(HERB_ENHANCING,"int",6);
    set_decay_time(10000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
